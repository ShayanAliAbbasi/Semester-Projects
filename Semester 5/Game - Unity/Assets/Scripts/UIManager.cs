using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class UIManager : MonoBehaviour
{
    static private UIManager instance = null;

    [SerializeField] private GameObject mainMenu = null;
    [SerializeField] private GameObject restartDeathMenu = null;
    [SerializeField] private GameObject restartCityFellMenu = null;
    [SerializeField] private GameObject continueMenu = null;
    [SerializeField] private GameObject ingameMenu = null;

    void Start()
    {   
        if (!instance)
        {
            instance = this;
        }
        else
        {
            Destroy(gameObject);
        }
    }

    void Update()
    {
        if (GameManager.instance.MainMenu())
        {
            MainMenu();
        }
        else
        {
            Deactivate(mainMenu);
        }

        if (GameManager.instance.GameStarted())
        {
            InGameMenu();
        }
        else
        {
            Deactivate(ingameMenu);
        }
    }

    void MainMenu()
    {
        Activate(mainMenu);

        Text highScore = mainMenu.transform.Find("HighScore_Text").gameObject.GetComponent<Text>();
        Text wavesSurvived = mainMenu.transform.Find("WavesSurvived_Text").gameObject.GetComponent<Text>();

        highScore.text = "<b>High Score:</b> " + ScoreManager.instance.HighScore().ToString("000000");
        wavesSurvived.text = "<b>Waves Survived:</b> " + WaveManager.instance.WavesSurvived().ToString("00");

        MainMenuInput();
    }

    void MainMenuInput()
    {
        if (Input.GetKeyDown(KeyCode.Return) || (Input.GetMouseButtonDown(0) && Input.mousePosition.y < (Screen.height * 0.75)))
        {
            GameManager.instance.SetGameStarted(true);
            GameManager.instance.SetMainMenu(false);

        }
        else if (Input.GetKeyDown(KeyCode.Escape))
        {
            Application.Quit();
        }

    }

    void InGameMenu()
    {
        Activate(ingameMenu);

        if (GameManager.instance.RestartDeath())
        {
            Activate(restartDeathMenu);

            GameOverInput();
        }
        else
        {
            Deactivate(restartDeathMenu);
        }

        if (GameManager.instance.RestartCityFell())
        {
            Activate(restartCityFellMenu);

            GameOverInput();
        }
        else
        {
            Deactivate(restartCityFellMenu);
        }

        if (GameManager.instance.Continue())
        {
            Activate(continueMenu);

            ingameMenu.transform.Find("Waves_Text").GetComponent<Text>().enabled = false;

            Time.timeScale = 0.0f;

            ContinueInput();
        }
        else
        {
            Deactivate(continueMenu);
        }

        if (!GameManager.instance.RestartCityFell() || !GameManager.instance.RestartDeath())
        {
            InGameInput();
        }
    }

    void InGameInput()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            GameManager.instance.SetContinue(true);
        }
    }

    void GameOverInput()
    {
        if (Input.GetKeyDown(KeyCode.Return) || Input.GetMouseButtonDown(0))
        {
            GameManager.restart = true;
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
        else if (Input.GetKeyDown(KeyCode.Escape))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }

    void ContinueInput()
    {
        if (Input.GetKeyDown(KeyCode.Return) || Input.GetMouseButtonDown(0))
        {
            Time.timeScale = 1.0f;

            GameManager.instance.SetContinue(false);

            ingameMenu.transform.Find("Waves_Text").GetComponent<Text>().enabled = true;
        }

        else if (Input.GetKeyDown(KeyCode.Escape))
        {
            Time.timeScale = 1.0f;

            ScoreManager.instance.Save();
            WaveManager.instance.Save();

            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }

    void Activate(GameObject gameObject)
    {
        if (gameObject.activeSelf == false)
            gameObject.SetActive(true);
    }

    void Deactivate(GameObject gameObject)
    {
        if (gameObject.activeSelf == true)
            gameObject.SetActive(false);
    }

    public void ResetScore()
    {
        ScoreManager.instance.ResetScore();
        
        WaveManager.instance.ResetWavesSurvived();
    }
}
