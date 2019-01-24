using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace boilerplateASP.Controllers
{
    public class HomeController : Controller
    {
        private SqlConnection conn = null;
        public ActionResult Login()
        {
            Session["currentUser"] = "";
            return View();
        }

        public void connectToDb()
        {
            string connetionString;

            connetionString = @"Data Source = LAPTOP-8A3HVFCJ\SQLEXPRESS; Initial Catalog = EnterpriseSystem; Integrated Security = SSPI";

            this.conn = new SqlConnection(connetionString);

            this.conn.Open();
        }

        public ActionResult Authenticate()
        {
            Session["currentUser"] = Request["name"];
            return View("Login");
        }

        public ActionResult Logout()
        {
            Session["currentUser"] = "";
            return View("Login");
        }

    }
}