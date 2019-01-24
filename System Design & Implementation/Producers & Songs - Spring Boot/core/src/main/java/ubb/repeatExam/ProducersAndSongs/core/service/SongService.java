package ubb.repeatExam.ProducersAndSongs.core.service;

import ubb.repeatExam.ProducersAndSongs.core.model.Producer;
import ubb.repeatExam.ProducersAndSongs.core.model.Song;

import java.util.List;
import java.util.Optional;

public interface SongService {
    List<Song> findAll();

    Song updateSong(Integer songId, String musicName, String genre, Integer mark);

    Song addSong(Song song);

    Optional<Song> deleteSong(Integer songId);

}
