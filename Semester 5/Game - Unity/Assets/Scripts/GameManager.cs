using System;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public static GameManager instance = null;

    bool mainMenu = true;
    bool gameOver = false;
    bool gameStarted = false;
    bool restartDeath = false;
    bool restartCityFell = false;
    bool continueGame = false;
    bool saveScore = false;
    bool saveWave = false;

    public static bool restart = false;

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

        if (restart)
        {
            mainMenu = false;
            gameOver = false;
            gameStarted = true;

            restart = false;
        }

    }

    public bool MainMenu()
    {
        return mainMenu;
    }

    public bool GameOver()
    {
        return gameOver;
    }

    public bool GameStarted()
    {
        return gameStarted;
    }

    public bool RestartDeath()
    {
        return restartDeath;
    }

    public bool RestartCityFell()
    {
        return restartCityFell;
    }

    public bool Continue()
    {
        return continueGame;
    }

    public bool SaveScore()
    {
        return saveScore;
    }

    public bool SaveWave()
    {
        return saveWave;
    }

    public void SetMainMenu(bool flag)
    {
        mainMenu = flag;
    }

    public void SetGameOver(bool flag)
    {
        gameOver = flag;
    }

    public void SetGameStarted(bool flag)
    {
        gameStarted = true;
    }

    public void SetRestartDeath(bool flag)
    {
        restartDeath = flag;
    }

    public void SetRestartCityFell(bool flag)
    {
        restartCityFell = flag;
    }

    public void SetContinue(bool flag)
    {
        continueGame = flag;
    }

    public void SetSaveScore(bool flag)
    {
        saveScore = flag;
    }
    public void SetSaveWave(bool flag)
    {
        saveWave = flag;
    }

    public void ResetAll()
    {
        mainMenu = true;
        gameOver = false;
        gameStarted = false;
        restartDeath = false;
        restartCityFell = false;
        continueGame = false;
        saveScore = false;
        saveWave = false;
    }

    private void OnApplicationQuit()
    {
        //Save high score and max waves survived before quitting

        ScoreManager.instance.Save();
        WaveManager.instance.Save();

        Application.Quit();
    }
}