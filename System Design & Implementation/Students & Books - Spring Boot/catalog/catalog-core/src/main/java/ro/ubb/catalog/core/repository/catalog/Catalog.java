package ro.ubb.catalog.core.repository.catalog;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.NoRepositoryBean;
import org.springframework.transaction.annotation.Transactional;
import ro.ubb.catalog.core.model.BaseEntity;

import java.io.Serializable;

@NoRepositoryBean
@Transactional
public interface Catalog<ID extends Serializable, T extends BaseEntity<ID>> extends JpaRepository<T, ID> {
}
