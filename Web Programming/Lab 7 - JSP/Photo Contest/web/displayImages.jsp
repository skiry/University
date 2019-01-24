<%@ page import="java.util.List" %>
<%@ page import="database.DBHelper" %><%--
  Created by IntelliJ IDEA.
  User: Skiry
  Date: 5/29/2019
  Time: 11:58 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>All images</title>
    <style>
        img {
            width: 250px;
            height: 350px;
        }

        #imagelist {
            font-size: 0;
            width: 1200px;
            margin: 0 auto;
        }
        #imagelist img {
            margin: 2px;
            border: 4px solid black;
            display: inline-block;
            border-radius: 10px;
        }

        #imagelist img:hover {
            border-color: white;
        }
    </style>
</head>
<body>
<a href=index.jsp>Home</a>
<div id="imagelist">
<%
    List<String> photoUrls = DBHelper.getPhotos();
    for(String url : photoUrls) {
        System.err.println(url);
        String redirectUrl = "VotePhoto?url=" + url; %>
        <a href=<%= redirectUrl %>><img alt="Image not loaded yet" src= <%= url %> ></a>
   <% } %>
</div>
</body>
</html>
