package ubb.repeatExam.ProducersAndSongs.core.service;

import ubb.repeatExam.ProducersAndSongs.core.model.Producer;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import ubb.repeatExam.ProducersAndSongs.core.model.Release;
import ubb.repeatExam.ProducersAndSongs.core.repository.ProducerRepository;

import java.util.List;
import java.util.Optional;

@Service
public class ProducerServiceImpl implements ProducerService{
    public static final Logger log = LoggerFactory.getLogger(ProducerServiceImpl.class);

    @Autowired
    private ProducerRepository producerRepository;

    @Override
    public List<Producer> findAll() {
        log.trace("findAll --- method entered");

        List<Producer> producers = producerRepository.findAll();

        log.trace("findAll: producers={}", producers);

        return producers;
    }

    @Override
    @Transactional
    public Producer updateProducer(Integer producerId, String name, String country, Integer age) {
        log.trace("updateProducer: name={}, country={}, age={}", name, country, age);

        Optional<Producer> producer = producerRepository.findById(producerId);

        producer.ifPresent(s->{
            s.setName(name);
            s.setCountry(country);
            s.setAge(age);
        });

        log.trace("updateProducer: producer={}", producer.get());

        return producer.orElse(null);
    }

    @Override
    @Transactional
    public Producer addProducer(Producer producer) {
        log.trace("addProducer: producer{}=", producer);

        producerRepository.save(producer);

        log.trace("addProducer: producer={}", producer);

        return producer;
    }

    @Override
    @Transactional
    public Optional<Producer> deleteProducer(Integer producerId) {
        log.trace("deleteProducer: producerId={}", producerId);

        Optional<Producer> p = producerRepository.findById(producerId);
        p.ifPresent(producer -> {
            producer.getSongs()
                            .forEach(song -> song.getReleases()
                            .removeIf(release -> release.getProducer().getId().equals(producerId)));
            producerRepository.delete(producer);
        });

        log.trace("deleteProducer: producer={}", p);

        return p;
    }

    @Override
    @Transactional
    public Producer updateRelease(Release release) {
        log.trace("updateRelease: release={}", release);

        Producer p = release.getProducer();
        Optional<Release> r = p.getReleases()
                .stream()
                .filter(rel -> rel.getSong().getId().equals(release.getSong().getId()))
                .findFirst();

        r.ifPresent(rel -> {
            rel.setDiskHouse(release.getDiskHouse());
            rel.setReleaseDate(release.getReleaseDate());
        });

        log.trace("updateRelease: release={}", r.get());

        return p;
    }
}
