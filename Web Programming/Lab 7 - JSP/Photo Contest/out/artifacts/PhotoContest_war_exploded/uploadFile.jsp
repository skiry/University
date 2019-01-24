<%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 5/29/2019
  Time: 9:48 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Photo Uploading Form</title>
</head>

<body>
<h3>File Upload:</h3>
Select a photo to upload: <br />
<form action = "UploadServlet" method = "post" enctype = "multipart/form-data">
    <input type = "file" name = "file" size = "50" />
    <br />
    <input type = "submit" value = "Upload Photo" />
</form>
</body>
</html>
