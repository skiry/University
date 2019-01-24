package ubb.repeatExam.ProducersAndSongs.core.model;

import lombok.*;
import org.hibernate.annotations.Cascade;
import org.springframework.transaction.annotation.Transactional;

import javax.persistence.*;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;

@Entity
@Table( name = "Producers" )
@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@Builder
public class Producer extends BaseEntity<Integer> {
    private String name;
    private String country;
    private int age;

    @OneToMany(mappedBy = "producer", cascade = CascadeType.ALL, fetch = FetchType.EAGER, orphanRemoval = true)
    @Cascade(org.hibernate.annotations.CascadeType.DELETE)
    private Set<Release> releases = new HashSet<>();

    @Transactional
    public void addRelease(final Release release){
        releases.add(release);
    }

    public Set<Song> getSongs() {
        return releases.stream()
                .map(Release::getSong).collect(Collectors.toUnmodifiableSet());
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Producer that = (Producer) o;

        return name.equals(that.name);
    }

    @Override
    public int hashCode() {
        return name.hashCode();
    }
}
