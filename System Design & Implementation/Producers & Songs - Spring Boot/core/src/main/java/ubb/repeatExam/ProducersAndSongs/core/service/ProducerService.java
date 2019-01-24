package ubb.repeatExam.ProducersAndSongs.core.service;

import ubb.repeatExam.ProducersAndSongs.core.model.Producer;
import ubb.repeatExam.ProducersAndSongs.core.model.Release;

import java.util.List;
import java.util.Optional;

public interface ProducerService {
    List<Producer> findAll();

    Producer updateProducer(Integer producerId, String name, String country, Integer age);

    Producer addProducer(Producer producer);

    Optional<Producer> deleteProducer(Integer producerId);

    Producer updateRelease(Release release);
}
