package ubb.repeatExam.ProducersAndSongs.web.controller;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import ubb.repeatExam.ProducersAndSongs.core.model.Song;
import ubb.repeatExam.ProducersAndSongs.core.service.SongService;
import ubb.repeatExam.ProducersAndSongs.web.converter.SongConverter;
import ubb.repeatExam.ProducersAndSongs.web.dto.ProducerDto;
import ubb.repeatExam.ProducersAndSongs.web.dto.SongDto;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping(value = "")
public class SongController {

    private static final Logger log = LoggerFactory.getLogger(SongController.class);

    @Autowired
    private SongService songService;

    @Autowired
    private SongConverter songConverter;


    @RequestMapping(value = "/songs", method = RequestMethod.GET)
    public List<SongDto> getSongs() {
        log.trace("getSongs");

        List<Song> songs = songService.findAll();

        log.trace("getSongs: songs={}", songs);

        return new ArrayList<>(songConverter.convertModelsToDtos(songs));
    }

    @RequestMapping(value = "/songs/{songId}", method = RequestMethod.PUT)
    public SongDto updateSong(
            @PathVariable final Integer songId,
            @RequestBody final SongDto songDto) {
        log.trace("updateSong: songId={}, songDtoMap={}", songId, songDto);

        Song song = songService.updateSong(songId,
                songDto.getMusicName(),
                songDto.getGenre(), songDto.getMark());

        SongDto result = songConverter.convertModelToDto(song);
        log.trace("updateSong: result={}", result);

        return result;
    }

    @RequestMapping(value = "/songs", method = RequestMethod.POST)
    public SongDto addSong(@RequestBody final SongDto songDto) {
        log.trace("addSong: songDtoMap={}", songDto);

        Song song = songService.addSong(songConverter.convertDtoToModel(songDto));

        SongDto result = songConverter.convertModelToDto(song);
        log.trace("addSong: result={}", result);

        return result;
    }

    @RequestMapping(value = "/songs/{songId}", method = RequestMethod.DELETE)
    public SongDto deleteSong(@PathVariable final Integer songId) {
        log.trace("deleteSong: songId={}", songId);

        Optional<Song> song = songService.deleteSong(songId);

        SongDto result = songConverter.convertModelToDto(song.get());

        log.trace("deleteSong: result={}", result);

        return result;
    }
}