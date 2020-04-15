using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public static Score instance = null;

    private int score = 0;

    public Text scoreText;

    void Start()
    {
        if (instance == null)
        {
            instance = this;
        }
        else
        {
            Destroy(gameObject);
        }
    }

    public void Save()
    {
        int highScore = HighScore();

        if (score > highScore)
        {
            PlayerPrefs.SetInt("highScore", score);
        }
    }

    public int HighScore()
    {
        return PlayerPrefs.GetInt("highScore", 0);
    }

    public void Add(int score)
    {
        this.score += score;
    }

    public void Deduct(int score)
    {
        if (!GameManager.instance.GameOver())
            this.score -= score;

        if (this.score < 0)
        {
            GameManager.instance.SetGameOver(true);
            GameManager.instance.SetRestartCityFell(true);
        }
    }

    public void Reset()
    {
        score = 0;
    }

    void Update()
    {
        if (score < 0)
        { 
            scoreText.text = "<color=red>XXXXXX</color>";
        }
        else
            scoreText.text = score.ToString("000000");

        if (GameManager.instance.SaveScore())
        {
            Save();
            GameManager.instance.SetSaveScore(false);
        }
    }
}
