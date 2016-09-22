#pragma once
#include <string>
#include <SFML/Audio.hpp>
namespace df {
	class Sound {
	private:
		//SFML sound
		sf::Sound sound;		
		//SFML sound buffer associated w/ sound
		sf::SoundBuffer sound_buffer;	
		//Text label to identify sound
		std::string label;
	public:
		Sound();
		~Sound();

		//Load sound buffer from file
		//Return 0 if ok, else -1
		int loadSound(std::string filename);

		//Set label associated with sound
		void setLabel(std::string new_label);
		//Get label associated with sound
		std::string getLabel() const;

		//Play sound
		//If loop is tru, repeat play when done
		void play(bool loop = false);

		//Stop sound
		void stop();
		
		//Pause sound
		void pause();

		//Return SFML sound
		sf::Sound getSound() const;
	};
}