package ubb.repeatExam.ProducersAndSongs.core.model;

import lombok.*;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Date;

@Entity
@Table(name = "Releases")
@IdClass(ProducerSongPK.class)
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@EqualsAndHashCode
@Builder
@ToString(exclude = {"producer", "song"})
public class Release implements Serializable {

    @Id
    @ManyToOne(optional = false, fetch = FetchType.EAGER)
    @JoinColumn(name = "producerId")
    private Producer producer;

    @Id
    @ManyToOne(optional = false, fetch = FetchType.EAGER)
    @JoinColumn(name = "songId")
    private Song song;

    @Column(name = "releaseDate", nullable = false)
    private Date releaseDate;

    @Column(name = "diskHouse", nullable = false)
    private String diskHouse;

}




