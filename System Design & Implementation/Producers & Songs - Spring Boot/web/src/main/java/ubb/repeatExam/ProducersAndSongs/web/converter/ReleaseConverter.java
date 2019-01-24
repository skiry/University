package ubb.repeatExam.ProducersAndSongs.web.converter;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import ubb.repeatExam.ProducersAndSongs.core.model.Producer;
import ubb.repeatExam.ProducersAndSongs.core.model.Release;
import ubb.repeatExam.ProducersAndSongs.core.model.Song;
import ubb.repeatExam.ProducersAndSongs.core.repository.ProducerRepository;
import ubb.repeatExam.ProducersAndSongs.core.repository.SongRepository;
import ubb.repeatExam.ProducersAndSongs.web.dto.ReleaseDto;

import java.util.Collection;
import java.util.Set;
import java.util.stream.Collectors;

@Component
public class ReleaseConverter {
    @Autowired
    private ProducerRepository producerRepository;
    @Autowired
    private SongRepository songRepository;

    public Release convertDtoToModel(ReleaseDto dto) {
        Release release = Release.builder()
                .producer(getProducerByName(dto.getProducer()))
                .song(getSongByName(dto.getSong()))
                .releaseDate(dto.getReleaseDate())
                .diskHouse(dto.getDiskHouse())
                .build();
        return release;
    }

    public ReleaseDto convertModelToDto(Release release) {
        ReleaseDto dto = ReleaseDto.builder()
                .producer(release.getProducer().getName())
                .song(release.getSong().getMusicName())
                .releaseDate(release.getReleaseDate())
                .diskHouse(release.getDiskHouse())
                .build();
        return dto;
    }

    public Set<ReleaseDto> convertModelsToDtos(Collection<Release> models) {
        return models.stream()
                .map(this::convertModelToDto)
                .collect(Collectors.toSet());
    }

    public Producer getProducerByName(String name){
        return producerRepository.findAll().stream().filter(p -> p.getName().equals(name)).findFirst().get();
    }

    public Song getSongByName(String name){
        return songRepository.findAll().stream().filter(s -> s.getMusicName().equals(name)).findFirst().get();
    }
}
