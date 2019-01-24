package ro.ubb.catalog.core.repository;

import ro.ubb.catalog.core.model.BaseEntity;
import ro.ubb.catalog.core.repository.catalog.Catalog;
import ro.ubb.catalog.core.repository.catalog.Repository;
import ro.ubb.catalog.core.validator.Validator;
import ro.ubb.catalog.core.validator.ValidatorException;

import java.io.Serializable;
import java.util.List;
import java.util.Optional;

public class DbRepository<ID extends Serializable, T extends BaseEntity<ID>> implements Repository<ID, T> {
    private final Catalog<ID, T> repo;
    private final Validator<ID, T> validator;

    public DbRepository(Catalog<ID, T> repo, Validator<ID, T> validator ) {
        this.repo = repo;
        this.validator = validator;
    }

    @Override
    public Optional<T> findOne( ID id ) {
        return repo.findById( id );
    }

    @Override
    public List<T> findAll() {
        return repo.findAll();
    }

    @Override
    public Optional<T> insert( T entity ) throws ValidatorException {
        validator.validate( entity );
        repo.save(entity);
        return Optional.empty();
    }

    @Override
    public Optional<T> update( T entity ) throws ValidatorException {
        validator.validate( entity );
        repo.save( entity );

        return Optional.of( entity );
    }

    @Override
    public Optional<T> delete ( ID id ) {
        if ( repo.existsById( id ) ) {
            Optional<T> prevEntity = repo.findById( id );
            repo.deleteById( id );
            return prevEntity;
        }

        return Optional.empty();
    }
}
