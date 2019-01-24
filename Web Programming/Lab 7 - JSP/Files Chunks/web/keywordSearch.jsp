<%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 6/17/2019
  Time: 5:16 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Search files</title>
</head>
<body>
You may fill in 0, 1, 2 or 3 inputs!
<form action="viewFiles.jsp" method="post">
    <input type="text" name="file[]"/><br/>
    <input type="text" name="file[]"/><br/>
    <input type="text" name="file[]"/><br/>
    <input type="submit" value="Search"/>
</form>

</body>
</html>
