package ubb.repeatExam.ProducersAndSongs.core.repository;

import ubb.repeatExam.ProducersAndSongs.core.model.BaseEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.NoRepositoryBean;
import org.springframework.transaction.annotation.Transactional;

import java.io.Serializable;

@NoRepositoryBean
@Transactional
public interface Repository<T extends BaseEntity<ID>, ID extends Serializable>
        extends JpaRepository<T, ID> {
}
