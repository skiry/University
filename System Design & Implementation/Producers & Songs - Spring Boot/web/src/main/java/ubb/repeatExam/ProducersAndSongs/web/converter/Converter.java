package ubb.repeatExam.ProducersAndSongs.web.converter;


import ubb.repeatExam.ProducersAndSongs.core.model.BaseEntity;
import ubb.repeatExam.ProducersAndSongs.web.dto.BaseDto;

public interface Converter<Model extends BaseEntity<Integer>, Dto extends BaseDto> {

    Model convertDtoToModel(Dto dto);

    Dto convertModelToDto(Model model);

}