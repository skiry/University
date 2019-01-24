package ro.ubb.catalog.core.validator;

/**
 * Exception base class for validator.
 */
public class ValidatorException extends RuntimeException {

    public ValidatorException( String message ) {
        super( message );
    }

    public ValidatorException( String message, Throwable cause ) {
        super( message, cause );
    }

    public ValidatorException( Throwable cause ) {
        super( cause );
    }
}
