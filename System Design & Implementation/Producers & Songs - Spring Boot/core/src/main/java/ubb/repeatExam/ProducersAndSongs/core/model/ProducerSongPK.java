package ubb.repeatExam.ProducersAndSongs.core.model;

import lombok.*;

import java.io.Serializable;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@EqualsAndHashCode
public class ProducerSongPK implements Serializable {
    private Producer producer;
    private Song song;
}
