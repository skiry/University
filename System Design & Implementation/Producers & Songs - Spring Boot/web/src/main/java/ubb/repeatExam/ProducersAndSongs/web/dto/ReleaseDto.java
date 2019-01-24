package ubb.repeatExam.ProducersAndSongs.web.dto;

import lombok.*;

import java.util.Date;

@NoArgsConstructor
@AllArgsConstructor
@Builder
@ToString
@Getter
@Setter
public class ReleaseDto {
    private String producer;
    private String song;

    //  Format:     "2020-10-10"
    private Date releaseDate;
    private String diskHouse;
}
