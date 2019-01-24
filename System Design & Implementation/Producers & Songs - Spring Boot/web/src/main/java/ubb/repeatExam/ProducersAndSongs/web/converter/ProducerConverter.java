package ubb.repeatExam.ProducersAndSongs.web.converter;

import ubb.repeatExam.ProducersAndSongs.core.model.Producer;
import org.springframework.stereotype.Component;
import ubb.repeatExam.ProducersAndSongs.web.dto.ProducerDto;

@Component
public class ProducerConverter extends BaseConverter<Producer, ProducerDto> {
    
    @Override
    public Producer convertDtoToModel(ProducerDto dto) {
        Producer producer = Producer.builder()
                .name(dto.getName())
                .country(dto.getCountry())
                .age(dto.getAge())
                .build();
        producer.setId(dto.getId());

        return producer;
    }

    @Override
    public ProducerDto convertModelToDto(Producer model) {
        ProducerDto dto = ProducerDto.builder()
                .name(model.getName())
                .country(model.getCountry())
                .age(model.getAge())
                .build();
        dto.setId(model.getId());

        return dto;
    }
}
