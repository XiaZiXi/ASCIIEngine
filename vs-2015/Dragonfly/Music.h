#pragma once
#include <string>
#include <SFML/Audio.hpp>

namespace df {
	class Music {
	private:
		//Music
		sf::Music music;
		//Text label for music
		std::string label;
		//SFML doesn't allow music copy
		Music(Music const&);
		//Or assignment
		void operator=(Music const&);
	public:
		Music();

		//Associate music buffer with file
		//Return 0 if success, else -1
		int loadMusic(std::string filename);

		//Set label associated with music
		void setLabel(std::string new_label);
		//Get label associated with music
		std::string getLabel() const;

		//Play music
		//If loop is tru, repeat play when done
		void play(bool loop = true);

		//stop music
		void stop();

		//pause music
		void pause();

		bool isPlaying() const;
		//Return SFML music
		sf::Music *getMusic();
	};
}