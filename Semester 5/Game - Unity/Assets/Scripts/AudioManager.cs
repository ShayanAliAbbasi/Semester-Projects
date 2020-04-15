using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioManager : MonoBehaviour
{
    public static AudioManager instance;

    [System.Serializable]
    class Sound
    {
        public string name;
        public AudioClip clip;
        public float volume;
        public float pitch;
        public AudioSource source;
    }

    [SerializeField]
    Sound[] sounds;

    // Start is called before the first frame update
    void Start()
    {
        if (instance == null)
        { 
            instance = this; 

            foreach(Sound s in sounds)
            {
                s.source = gameObject.AddComponent<AudioSource>();
                s.source.clip = s.clip;
            }
        }
        else
            Destroy(gameObject);
    }

    public void Play(string audioName, float volume, float pitch)
    {
        foreach (Sound s in sounds)
        {
            if (s.name == audioName)
            {
                s.source.volume = s.volume * (1 + Random.Range(-0.1f, 0.1f));
                s.source.pitch = s.pitch * (1 + Random.Range(-0.5f, 0.5f));
                s.source.Play();
                return;
            }
        }

    }
}
