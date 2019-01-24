package ro.ubb.catalog.core.validator;

import ro.ubb.catalog.core.model.BaseEntity;

/**
 * Validator interface for base model.
 */
public interface Validator<ID, T extends BaseEntity<ID>> {
    /**
     * Validates an entity.
     * @param entity - the entity to be validated.
     * @throws ValidatorException - if the entity is not valid.
     */
    void validate( T entity ) throws ValidatorException;
}
