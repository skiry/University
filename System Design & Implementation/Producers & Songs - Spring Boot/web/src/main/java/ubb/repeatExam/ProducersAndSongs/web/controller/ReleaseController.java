package ubb.repeatExam.ProducersAndSongs.web.controller;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.*;
import ubb.repeatExam.ProducersAndSongs.core.model.Producer;
import ubb.repeatExam.ProducersAndSongs.core.model.Release;
import ubb.repeatExam.ProducersAndSongs.core.model.Song;
import ubb.repeatExam.ProducersAndSongs.core.repository.ProducerRepository;
import ubb.repeatExam.ProducersAndSongs.core.repository.SongRepository;
import ubb.repeatExam.ProducersAndSongs.core.service.ProducerService;
import ubb.repeatExam.ProducersAndSongs.web.converter.ReleaseConverter;
import ubb.repeatExam.ProducersAndSongs.web.dto.ReleaseDto;
import ubb.repeatExam.ProducersAndSongs.web.dto.SongDto;

import java.util.HashSet;
import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;

@RestController
@RequestMapping(value = "")
public class ReleaseController {

    @Autowired
    private ReleaseConverter releaseConverter;

    @Autowired
    private ProducerRepository producerRepository;

    @Autowired
    private SongRepository songRepository;

    @Autowired
    private ProducerService producerService;

    @Transactional
    @RequestMapping(value = "/releases", method = RequestMethod.POST)
    public ReleaseDto addRelease(@RequestBody ReleaseDto releaseDto) {
        System.out.println(releaseDto);
        final Release release = releaseConverter.convertDtoToModel(releaseDto);

        Producer producer = releaseConverter.getProducerByName(releaseDto.getProducer());
        Song song = releaseConverter.getSongByName(releaseDto.getSong());
        producer.addRelease(release);
        song.addRelease(release);

        return releaseConverter.convertModelToDto(release);
    }

    @RequestMapping(value = "/releases", method = RequestMethod.GET)
    public Set<ReleaseDto> getAll() {
        Set<ReleaseDto> releases = new HashSet<>();
        final List<Producer> producers = producerRepository.findAll();

        producers.forEach(producer -> {
            releases.addAll(producer
                    .getReleases()
                    .stream()
                    .map(release -> releaseConverter.convertModelToDto(release))
                    .collect(Collectors.toSet()));
        });

        return releases;
    }

    @RequestMapping(value = "/songs/{producer/{song}", method = RequestMethod.PUT)
    public void updateSong(
            @PathVariable final String producer,
            @PathVariable final String song,
            @RequestBody final ReleaseDto releaseDto) {

        producerService.updateRelease(releaseConverter.convertDtoToModel(releaseDto));
    }
}
