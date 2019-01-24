package ubb.repeatExam.ProducersAndSongs.web.converter;

import org.springframework.stereotype.Component;
import ubb.repeatExam.ProducersAndSongs.core.model.Song;
import ubb.repeatExam.ProducersAndSongs.web.dto.SongDto;

@Component
public class SongConverter extends BaseConverter<Song, SongDto> {

    @Override
    public Song convertDtoToModel(SongDto dto) {
        Song producer = Song.builder()
                .musicName(dto.getMusicName())
                .genre(dto.getGenre())
                .mark(dto.getMark())
                .build();
        producer.setId(dto.getId());

        return producer;
    }

    @Override
    public SongDto convertModelToDto(Song model) {
        SongDto dto = SongDto.builder()
                .musicName(model.getMusicName())
                .genre(model.getGenre())
                .mark(model.getMark())
                .build();
        dto.setId(model.getId());

        return dto;
    }
}
