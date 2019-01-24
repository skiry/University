<html>
    <head>
        <title>Searching an user...</title>
        <link rel="stylesheet" type="text/css" href="style.css">
        <script>
        var last = null;
            function showResult(str) {
                if (str.length==0) {
                    document.getElementById("livesearch").innerHTML="";
                    document.getElementById("livesearch").style.border="0px";
                    return;
                }

                if (window.XMLHttpRequest) {
                    // code for IE7+, Firefox, Chrome, Opera, Safari
                    xmlhttpRoles=new XMLHttpRequest();
                    xmlhttpNames=new XMLHttpRequest();
                } else {  // code for IE6, IE5
                    xmlhttpRoles=new ActiveXObject("Microsoft.XMLHTTP");
                    xmlhttpNames=new ActiveXObject("Microsoft.XMLHTTP");
                }

                xmlhttpRoles.onreadystatechange=function() {
                    if (this.readyState==4 && this.status==200) {
                    document.getElementById("livesearch").innerHTML=this.responseText;
                    document.getElementById("livesearch").style.border="1px solid #A5ACB2";
                        if(last == null) {
                            document.getElementById("lastSearch").innerHTML="<h2>No last search</h2>";                            
                        }
                        else{
                            document.getElementById("lastSearch").innerHTML="<h2>Last search is " + last + "</h2>";
                        }
                        last = str;
                    }
                }

                xmlhttpRoles.open("GET","liveSearchRole.php?q="+str,true);
                xmlhttpRoles.send();

                xmlhttpNames.onreadystatechange=function() {
                    if (this.readyState==4 && this.status==200) {
                    document.getElementById("specificRoleUsers").innerHTML=this.responseText;
                    }
                }

                xmlhttpNames.open("GET","name-role-Helper.php?q="+str,true);
                xmlhttpNames.send();
            }

            function showUser(str) {
                var xhttp;
                if (str == "") {
                    document.getElementById("txtHint").innerHTML = "";
                    return;
                }
                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("txtHint").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "liveSearchName.php?q="+str, true);
                xhttp.send();
                ok = 1;
            }
        </script>
    </head>

    <body>
        <header>
            <h1 class="banner">Enterprise System</h1>
        </header>

        <form action=""> 
            <label>Get user by role!</label>
            <input type="text" size="30" onkeyup="showResult(this.value)">
            <div id="livesearch" style="margin-left:20"></div>
        </form>

        <form action=""> 
            <label>Get data by Full Name!</label>
            <select name="users" id="specificRoleUsers" onchange="showUser(this.value)" style="margin-left:20">
                <option value="">Select an user</option>
            </select>
        </form>

        <label id="lastSearch" style="display: block; text-align: center"></label>
        <div id="txtHint"></div>
    </body>
</html>