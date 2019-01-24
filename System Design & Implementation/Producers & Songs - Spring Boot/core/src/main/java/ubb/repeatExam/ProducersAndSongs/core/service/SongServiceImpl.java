package ubb.repeatExam.ProducersAndSongs.core.service;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import ubb.repeatExam.ProducersAndSongs.core.model.Song;
import ubb.repeatExam.ProducersAndSongs.core.repository.SongRepository;

import java.util.List;
import java.util.Optional;

@Service
public class SongServiceImpl implements SongService{
    public static final Logger log = LoggerFactory.getLogger(ProducerServiceImpl.class);

    @Autowired
    private SongRepository songRepository;

    @Override
    public List<Song> findAll() {
        log.trace("findAll --- method entered");

        List<Song> songs= songRepository.findAll();

        log.trace("findAll: songs={}", songs);

        return songs;
    }

    @Override
    @Transactional
    public Song updateSong(Integer songId, String musicName, String genre, Integer mark) {
        log.trace("updateSong: musicName={}, genre={}, mark={}", musicName, genre, mark);

        Optional<Song> song = songRepository.findById(songId);

        song.ifPresent(s->{
            s.setMusicName(musicName);
            s.setGenre(genre);
            s.setMark(mark);
        });

        log.trace("updateSong: song={}", song.get());

        return song.orElse(null);
    }

    @Override
    public Song addSong(Song song) {
        log.trace("addSong: song={}", song);

        songRepository.save(song);

        log.trace("addSong: song={}", song);

        return song;
    }

    @Override
    public Optional<Song> deleteSong(Integer songId) {
        log.trace("deleteSong: songId={}", songId);

        Optional<Song> song = songRepository.findById(songId);
        song.ifPresent(s -> {
            s.getProducers()
                    .forEach(producer -> producer.getReleases()
                            .removeIf(release -> release.getSong().getId().equals(songId)));
            songRepository.delete(s);
        });
        log.trace("deleteSong: song={}", song);

        return song;
    }
}
