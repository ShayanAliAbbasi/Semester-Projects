using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class WaveManager : MonoBehaviour
{

    public enum State { HALT, COUNTING, SPAWNING, WAITING };

    State state = State.HALT;

    private int currentWave = 0;
    private Wave wave;
    private bool colorToggled = false;

    private Vector3[] spawnPoints = new Vector3[5];

    public static WaveManager instance = null;

    public GameObject[] allEnemies;

    public float timeBetweenWaves = 2.5f;
    public float spawnCountdownTime = 2.5f;
    public float checkCountdownTime = 1.0f;

    public int wavesToColorToggle = 5;
    public Color backgroundToggleColor;
    public Color skyToggleColor;

    public Text waveText;
    
    class Wave
    {
        public int number;
        public int count;
        public float rate;

        public Wave(int waveNumber, int totalEnemies, float spawnRate)
        {
            number = waveNumber;
            count = totalEnemies;
            rate = spawnRate;
        }
    }

    private void Start()
    {
        if (instance == null)
        {
            instance = this;
        }
        else
            Destroy(gameObject);

        spawnCountdownTime = timeBetweenWaves;
    }

    private void Update()
    {
        if (GameManager.instance.SaveWave())
        {
            Save();

            GameManager.instance.SetSaveWave(false);
        }

        if (state != State.HALT && !GameManager.instance.GameStarted() || GameManager.instance.GameOver())
            state = State.HALT;
        else if (state == State.HALT && GameManager.instance.GameStarted())
            state = State.COUNTING;

        if (state == State.HALT)
            return;

        if (state == State.COUNTING)
        {
            if (spawnCountdownTime <= 0)
            {
                waveText.gameObject.SetActive(false);

                if (state != State.SPAWNING && state != State.WAITING)
                {
                    StartCoroutine(GenerateWave());
                }
            }
            else
            {
                spawnCountdownTime -= Time.deltaTime;
            }
        }

        else if (state == State.WAITING)
        {
            if (AllEnemiesDead())
            {
                spawnCountdownTime = timeBetweenWaves;

                if (currentWave % wavesToColorToggle == 0)
                    ToggleBackgroundColor();

                state = State.COUNTING;

                waveText.text = "WAVE <b><color=red>" + (currentWave + 1) + "</color></b>" + " INCOMING";
                if (!waveText.gameObject.activeSelf) 
                    waveText.gameObject.SetActive(true);
            }
        }

        if (currentWave == 0)
        {
            waveText.text = "WAVE <b><color=red>1</color></b>" + " INCOMING";
            if (!waveText.gameObject.activeSelf)
                waveText.gameObject.SetActive(true);
        }
    }

    private IEnumerator GenerateWave()
    {
        currentWave++;

        state = State.SPAWNING;

        wave = new Wave(currentWave, currentWave, currentWave / 5f);

        for (int i = 0; i < wave.count; i++)
        {
            GenerateSpawnPoints();

            Instantiate(allEnemies[Random.Range(0, allEnemies.Length)], spawnPoints[Random.Range(0, spawnPoints.Length)], transform.rotation);

            yield return new WaitForSeconds(1f / wave.rate);
        }

        state = State.WAITING;

        yield break;
    }

    private bool AllEnemiesDead()
    {
        checkCountdownTime -= Time.deltaTime;

        if (checkCountdownTime <= 0)
        {
            checkCountdownTime = 1.0f;

            if (GameObject.FindGameObjectWithTag("Enemy") == null)
            {
                return true;
            }

            return false;
        }

        return false;
    }

    static float zOffestToStopGlitch = 0.0f;
    private void GenerateSpawnPoints()
    {
        Camera camera = Camera.main;

        const float xOffsetFromEdge = 0.1f;

        Vector3 topRight = camera.ViewportToWorldPoint(new Vector3(1f + xOffsetFromEdge, 1f - 0.1f, camera.nearClipPlane));
        Vector3 betweenTopAndMiddleRight = camera.ViewportToWorldPoint(new Vector3(1f + xOffsetFromEdge, 0.3f, camera.nearClipPlane));
        Vector3 middleRight = camera.ViewportToWorldPoint(new Vector3(1f + xOffsetFromEdge, 0.5f, camera.nearClipPlane));
        Vector3 betweenMiddleAndBottomRight = camera.ViewportToWorldPoint(new Vector3(1f + xOffsetFromEdge, 0.7f, camera.nearClipPlane));
        Vector3 bottomRight = camera.ViewportToWorldPoint(new Vector3(1f + xOffsetFromEdge, 0f + 0.1f, camera.nearClipPlane));

  
        spawnPoints[0] = topRight + new Vector3(0f, 0f, zOffestToStopGlitch++);
        spawnPoints[1] = betweenTopAndMiddleRight + new Vector3(0f, 0f, zOffestToStopGlitch++); ;
        spawnPoints[2] = middleRight + new Vector3(0f, 0f, zOffestToStopGlitch++); ;
        spawnPoints[3] = betweenMiddleAndBottomRight + new Vector3(0f, 0f, zOffestToStopGlitch++); ;
        spawnPoints[4] = bottomRight + new Vector3(0f, 0f, zOffestToStopGlitch++);
    }

    public void Save()
    {
        int wavesSurvived = WavesSurvived();

        if (currentWave - 1 > wavesSurvived)
        {
            PlayerPrefs.SetInt("wavesSurvived", currentWave - 1);
        }
    }

    public int WavesSurvived()
    {
        return PlayerPrefs.GetInt("wavesSurvived", 0);
    }

    public void ResetWavesSurvived()
    {
        Reset();
        PlayerPrefs.SetInt("wavesSurvived", 0);
    }

    public int CurrentWave()
    {
        return currentWave;
    }

    public State GetState()
    {
        return state;
    }

    public void ToggleBackgroundColor()
    {
        SpriteRenderer[] renderers = FindObjectsOfType<SpriteRenderer>();

        foreach (SpriteRenderer spr in renderers)
        {
            if (spr.material.HasProperty("_Color") && LayerMask.NameToLayer("Background") == spr.gameObject.layer)
            {
                if (!colorToggled)
                {
                    if (spr.gameObject.tag == "Sky")
                        spr.material.SetColor("_Color", skyToggleColor);
                    else
                        spr.material.SetColor("_Color", backgroundToggleColor);
                }
                else
                {
                    Color c = spr.material.color;

                    float maxColor = c.maxColorComponent;

                    spr.material.SetColor("_Color", new Color(maxColor, maxColor, maxColor));
                }
            }
        }

        colorToggled = !colorToggled;
    }

    public void Reset()
    {
        state = State.HALT;

        currentWave = 0;

        timeBetweenWaves = 2.5f;
        spawnCountdownTime = 2.5f;
        checkCountdownTime = 1.0f;

        colorToggled = false;
    }

}
