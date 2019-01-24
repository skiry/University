package ro.ubb.catalog.core.repository.catalog;

import ro.ubb.catalog.core.model.BaseEntity;
import ro.ubb.catalog.core.validator.ValidatorException;

import java.io.Serializable;
import java.util.Optional;

/**
 * Interface for generic CRUD operations on a repository for a specific type.
 *
 * @author radu.
 *
 */
public interface Repository<ID extends Serializable, T extends BaseEntity<ID>> {
    /**
     * Find the entity with the given {@code id}.
     *
     * @param id
     *            must be not null.
     * @return an {@code Optional} encapsulating the entity with the given id.
     * @throws IllegalArgumentException
     *             if the given id is null.
     */
    Optional<T> findOne( ID id );

    /**
     * @return all model.
     */
    Iterable<T> findAll();

    /**
     * Inserts the given entity.
     *
     * @param entity
     *            must not be null.
     * @return an {@code Optional} - null if the entity was inserted otherwise (e.g. id already exists) returns the entity.
     * @throws IllegalArgumentException
     *             if the given entity is null.
     * @throws ValidatorException
     *             if the entity is not valid.
     */
    Optional<T> insert( T entity ) throws ValidatorException;

    /**
     * Removes the entity with the given id.
     *
     * @param id
     *            must not be null.
     * @return an {@code Optional} - null if there is no entity with the given id, otherwise the removed entity.
     * @throws IllegalArgumentException
     *             if the given id is null.
     */
    Optional<T> delete ( ID id );

    /**
     * Updates the given entity.
     *
     * @param entity
     *            must not be null.
     * @return an {@code Optional} - null if the entity was updated otherwise (e.g. id does not exist) returns the
     *         entity.
     * @throws IllegalArgumentException
     *             if the given entity is null.
     * @throws ValidatorException
     *             if the entity is not valid.
     */
    Optional<T> update( T entity ) throws ValidatorException;
}
