package ubb.repeatExam.ProducersAndSongs.core.model;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;

import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.MappedSuperclass;
import java.io.Serializable;

@MappedSuperclass
@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString
public class BaseEntity<ID> implements Serializable {
    @Id
    @GeneratedValue
    private ID id;
}
