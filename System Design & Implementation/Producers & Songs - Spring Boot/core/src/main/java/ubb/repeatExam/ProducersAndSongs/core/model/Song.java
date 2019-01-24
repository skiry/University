package ubb.repeatExam.ProducersAndSongs.core.model;

import lombok.*;
import org.hibernate.annotations.Cascade;
import org.springframework.transaction.annotation.Transactional;

import javax.persistence.*;
import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;

@Entity
@Table( name = "Songs" )
@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@Builder
public class Song extends BaseEntity<Integer> {
    private String musicName;
    private String genre;
    private int mark;

    @OneToMany(mappedBy = "song", cascade = CascadeType.ALL, fetch = FetchType.EAGER, orphanRemoval = true)
    @Cascade(org.hibernate.annotations.CascadeType.DELETE)
    private Set<Release> releases = new HashSet<>();

    @Transactional
    public void addRelease(final Release release){
        releases.add(release);
    }

    public Set<Producer> getProducers() {
        return releases.stream()
                .map(Release::getProducer).collect(Collectors.toUnmodifiableSet());
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Song that = (Song) o;

        return musicName.equals(that.musicName);
    }

    @Override
    public int hashCode() {
        return musicName.hashCode();
    }
}
