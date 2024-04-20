using namespace std;
class MusicPlayer {
public:
    string year;
    string title;
    string artist;
    string album;
    string genre;
    float duration;
    bool playing;

    MusicPlayer() {
        year = "";
        title = "";
        artist = "";
        album = "";
        genre = "";
        duration = 0.0;
        playing = false;
    }

    MusicPlayer(string year, string title, string artist, string album, string genre, float duration) {
        this->year = year;
        this->title = title;
        this->artist = artist;
        this->album = album;
        this->genre = genre;
        this->duration = duration;
        this->playing = false;
    }
    
};
