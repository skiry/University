<%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 6/16/2019
  Time: 5:13 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Contents</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.0/jquery.min.js"></script>
    <script>
        $(document).ready(function() {
            function updateContents() {
                var xhttp;

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function () {
                    if (this.readyState === 4 && this.status === 200) {
                        $("#contents")
                            .empty()
                            .append(this.responseText);
                    }
                };
                xhttp.open("GET", "GetLastServlet", true);
                xhttp.send();
            }
            function getUpdates() {
                var xhttp;

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function () {
                    if (this.readyState === 4 && this.status === 200) {
                        if (this.responseText.length > 0) {
                            alert("New content was added!");
                            updateContents();
                            return false;
                        }
                    }
                };
                console.log($("#div0").text());
                xhttp.open("GET", "UpdateInfoServlet?t1=" + $("#div0").text() + "&t2=" +
                    $("#div1").text() + "&t3=" + $("#div2").text()+ "&t4=" + $("#div3").text(), true);
                xhttp.send();
            }

            $(function() {
                var counter = 0;

                function showDiv () {
                    getUpdates();
                    if (counter % 4 === 0) {
                        $("#div0").css({"visibility": "visible"});
                        $("#div1").css({"visibility": "hidden"});
                        $("#div2").css({"visibility": "hidden"});
                        $("#div3").css({"visibility": "hidden"});
                    }
                    else if (counter % 4 === 1){
                        $("#div1").css({"visibility": "visible"});
                        $("#div0").css({"visibility": "hidden"});
                        $("#div2").css({"visibility": "hidden"});
                        $("#div3").css({"visibility": "hidden"});
                    }
                    else if (counter % 4 === 2){
                        $("#div2").css({"visibility": "visible"});
                        $("#div1").css({"visibility": "hidden"});
                        $("#div0").css({"visibility": "hidden"});
                        $("#div3").css({"visibility": "hidden"});
                    }
                    else if (counter % 4 === 3){
                        $("#div3").css({"visibility": "visible"});
                        $("#div1").css({"visibility": "hidden"});
                        $("#div2").css({"visibility": "hidden"});
                        $("#div0").css({"visibility": "hidden"});
                    }
                    counter++;
                }

                showDiv();
                setInterval(function () {
                    showDiv();
                }, 3 * 1000);

            });
        });
    </script>
</head>
<body>

<div id="contents">
</div>

</body>
</html>
