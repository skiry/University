package ubb.repeatExam.ProducersAndSongs.web.controller;


import ubb.repeatExam.ProducersAndSongs.core.model.Producer;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import ubb.repeatExam.ProducersAndSongs.core.service.ProducerService;
import ubb.repeatExam.ProducersAndSongs.web.converter.ProducerConverter;
import ubb.repeatExam.ProducersAndSongs.web.dto.ProducerDto;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping(value = "")
public class ProducerController {

    private static final Logger log = LoggerFactory.getLogger(ProducerController.class);

    @Autowired
    private ProducerService producerService;

    @Autowired
    private ProducerConverter producerConverter;


    @RequestMapping(value = "/producers", method = RequestMethod.GET)
    public List<ProducerDto> getProducers() {
        log.trace("getProducers");

        List<Producer> producers = producerService.findAll();

        log.trace("getProducers: producers={}", producers);

        return new ArrayList<>(producerConverter.convertModelsToDtos(producers));
    }

    @RequestMapping(value = "/producers/{producerId}", method = RequestMethod.PUT)
    public ProducerDto updateProducer(
            @PathVariable final Integer producerId,
            @RequestBody final ProducerDto producerDto) {
        log.trace("updateProducer: producerId={}, producerDtoMap={}", producerId, producerDto);

        Producer producer = producerService.updateProducer(producerId,
                producerDto.getName(),
                producerDto.getCountry(), producerDto.getAge());

        ProducerDto result = producerConverter.convertModelToDto(producer);

        log.trace("updateProducer: result={}", result);

        return result;
    }

    @RequestMapping(value = "/producers", method = RequestMethod.POST)
    public ProducerDto addProducer(@RequestBody final ProducerDto producerDto) {
        log.trace("addProducer: producerDtoMap={}", producerDto);

        Producer producer = producerService.
                addProducer(producerConverter.convertDtoToModel(producerDto));

        ProducerDto result = producerConverter.convertModelToDto(producer);

        log.trace("addProducer: result={}", result);

        return result;
    }

    @RequestMapping(value = "/producers/{producerId}", method = RequestMethod.DELETE)
    public ProducerDto addProducer(@PathVariable final Integer producerId) {
        log.trace("deleteProducer: producerId={}", producerId);

        Optional<Producer> producer = producerService.deleteProducer(producerId);

        ProducerDto result = producerConverter.convertModelToDto(producer.get());

        log.trace("deleteProducer: result={}", result);

        return result;
    }

}