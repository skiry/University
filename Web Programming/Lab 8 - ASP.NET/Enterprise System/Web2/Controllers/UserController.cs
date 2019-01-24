using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Web2.Models;

namespace Web2.Controllers
{
    public class UserController : Controller
    {
        // GET: User
        private SqlConnection conn = null;

        public ActionResult Index(String name = "")
        {
            if ((bool) Session["loggedIn"] == false)
            {
                return RedirectToAction("Login");
            }
            if (this.conn == null)
            {
                connectToDb();
            }
            if (name != "")
            {
                List<User> users = getUsers();
                List<User> finalUsers = new List<User>();
                foreach(User u in users)
                {
                    if (u.Name.Contains(name))
                    {
                        finalUsers.Add(u);
                    }
                }
                return View(finalUsers);
            }
            return View(getUsers());
        }

        public void connectToDb()
        {
            string connetionString;

            connetionString = @"Data Source = LAPTOP-8A3HVFCJ\SQLEXPRESS; Initial Catalog = EnterpriseSystem; Integrated Security = SSPI";

            this.conn = new SqlConnection(connetionString);

            this.conn.Open();
        }

        public List<User> getUsers()
        {
            SqlCommand command;
            SqlDataReader dataReader;
            String sql;
            if(this.conn == null)
            {
                connectToDb();
            }
            List<User> users = new List<User>();
            sql = "Select * from Users";

            command = new SqlCommand(sql, this.conn);

            dataReader = command.ExecuteReader();
            while (dataReader.Read())
            {
                users.Add(new Models.User
                {
                    UserId = dataReader.GetInt32(0),
                    Name = dataReader.GetString(1),
                    Password = dataReader.GetString(2),
                    Age = dataReader.GetInt32(3),
                    Role = dataReader.GetString(4),
                    Email = dataReader.GetString(5),
                    Webpage = dataReader.GetString(6)
                });
            }
            
            dataReader.Close();
            return users;
        }

        public ActionResult Edit(int UserId)
        {
            if (!(bool)Session["loggedIn"])
            {
                return RedirectToAction("Login");
            }
            User u = new User();
            List<User> users = getUsers();
            foreach(User user in users)
            {
                if(user.UserId == UserId)
                {
                    u = user;
                }
            }

            return View(u);
        }

        [HttpPost]
        public ActionResult Edit(User user)
        {
            if (!(bool)Session["loggedIn"])
            {
                return RedirectToAction("Login");
            }
            if (this.conn == null)
            {
                connectToDb();
            }

            SqlCommand command = new SqlCommand(null, this.conn);

            // Create and prepare an SQL statement.
            command.CommandText =
                "UPDATE Users " +
                "SET Name = @name, Age = @age, Role = @role, Email = @email, Webpage = @webpage " +
                "WHERE Id = @id;";
            SqlParameter idParam = new SqlParameter("@id", SqlDbType.Int, 50);
            SqlParameter nameParam = new SqlParameter("@name", SqlDbType.VarChar, 50);
            SqlParameter ageParam = new SqlParameter("@age", SqlDbType.VarChar, 50);
            SqlParameter roleParam = new SqlParameter("@role", SqlDbType.VarChar, 50);
            SqlParameter emailParam = new SqlParameter("@email", SqlDbType.VarChar, 50);
            SqlParameter webpageParam = new SqlParameter("@webpage", SqlDbType.VarChar, 50);

            idParam.Value = user.UserId;
            nameParam.Value = user.Name;
            ageParam.Value = user.Age;
            roleParam.Value = user.Email;
            emailParam.Value = user.Email;
            webpageParam.Value = user.Webpage;

            command.Parameters.Add(nameParam);
            command.Parameters.Add(ageParam);
            command.Parameters.Add(roleParam);
            command.Parameters.Add(emailParam);
            command.Parameters.Add(webpageParam);
            command.Parameters.Add(idParam);

            // Call Prepare after setting the Commandtext and Parameters.
            command.Prepare();
            command.ExecuteNonQuery();

            return RedirectToAction("Index");
        }

        [HttpPost]
        public ActionResult Create(User user)
        {
            if (!(bool)Session["loggedIn"])
            {
                return RedirectToAction("Login");
            }
            if (this.conn == null)
            {
                connectToDb();
            }

            SqlCommand command = new SqlCommand(null, this.conn);

            // Create and prepare an SQL statement.
            command.CommandText =
                "INSERT INTO Users " +
                "VALUES(@id, @name, @password, @age, @role, @email, @webpage);";
            SqlParameter idParam = new SqlParameter("@id", SqlDbType.Int, 50);
            SqlParameter passParam = new SqlParameter("@password", SqlDbType.VarChar, 50);
            SqlParameter nameParam = new SqlParameter("@name", SqlDbType.VarChar, 50);
            SqlParameter ageParam = new SqlParameter("@age", SqlDbType.Int, 50);
            SqlParameter roleParam = new SqlParameter("@role", SqlDbType.VarChar, 50);
            SqlParameter emailParam = new SqlParameter("@email", SqlDbType.VarChar, 50);
            SqlParameter webpageParam = new SqlParameter("@webpage", SqlDbType.VarChar, 50);

            List<User> users = getUsers();
            int maxId = 0;
            foreach (User u in users)
            {
                if (u.UserId > maxId)
                {
                    maxId = u.UserId;
                }
            }
            ++maxId;

            idParam.Value = maxId;
            nameParam.Value = user.Name;
            passParam.Value = user.Password;
            ageParam.Value = user.Age;
            roleParam.Value = user.Email;
            emailParam.Value = user.Email;
            webpageParam.Value = user.Webpage;

            command.Parameters.Add(nameParam);
            command.Parameters.Add(passParam);
            command.Parameters.Add(ageParam);
            command.Parameters.Add(roleParam);
            command.Parameters.Add(emailParam);
            command.Parameters.Add(webpageParam);
            command.Parameters.Add(idParam);

            // Call Prepare after setting the Commandtext and Parameters.
            command.Prepare();
            command.ExecuteNonQuery();

            return RedirectToAction("Index");
        }

        public ActionResult Create()
        {
            if (!(bool)Session["loggedIn"])
            {
                return RedirectToAction("Login");
            }
            return View(new User());
        }
        
        public ActionResult Delete(int id)
        {
            if (!(bool)Session["loggedIn"])
            {
                return RedirectToAction("Login");
            }
            Console.WriteLine(id);
            if (this.conn == null)
            {
                connectToDb();
            }

            SqlCommand command = new SqlCommand(null, this.conn);

            // Create and prepare an SQL statement.
            command.CommandText =
                "DELETE FROM Users " +
                "WHERE Id = @id;";
            SqlParameter idParam = new SqlParameter("@id", SqlDbType.Int, 50);

            idParam.Value = id;
            command.Parameters.Add(idParam);

            // Call Prepare after setting the Commandtext and Parameters.
            command.Prepare();
            command.ExecuteNonQuery();

            return RedirectToAction("Index");
        }

        public ActionResult RoleSearch()
        {
            if (!(bool)Session["loggedIn"])
            {
                return RedirectToAction("Login");
            }
            return View();
        }

        public ActionResult UserSearch()
        {
            if (!(bool)Session["loggedIn"])
            {
                return RedirectToAction("Login");
            }
            if(Request.QueryString["name"] != null)
            {
                return RedirectToAction("Index", new { name = Request.QueryString["name"] });
            }
            return View(new User());
        }

        public ActionResult Login()
        {
            Session["loggedIn"] = false;
            if ((bool)Session["loggedIn"])
            {
                return RedirectToAction("Index");
            }
            return View(new User());
        }
       
        

        [HttpPost]
        public ActionResult Login(User user)
        {
            if(this.conn == null)
            {
                connectToDb();
            }
            SqlDataReader dataReader;
            SqlCommand command = new SqlCommand(null, this.conn);
            command.CommandText = "Select * from Users WHERE Name = @name and Password = @pass;";
            Console.WriteLine(user.Name, user.Password);
            SqlParameter nameParam = new SqlParameter("@name", SqlDbType.VarChar, 50);
            SqlParameter passParam = new SqlParameter("@pass", SqlDbType.VarChar, 50);

            nameParam.Value = user.Name;
            passParam.Value = user.Password;
            command.Parameters.Add(nameParam);
            command.Parameters.Add(passParam);
            // Call Prepare after setting the Commandtext and Parameters.
            command.Prepare();
            int nr = 0;
            dataReader = command.ExecuteReader();
            while (dataReader.Read())
            {
                nr++;
            }
            
            dataReader.Close();

            if(nr == 1)
            {
                Session["loggedIn"] = true;
                return RedirectToAction("Index");
            }

            return RedirectToAction("Login");
        }

        public string GetUsersByRole()
        {
            string role = Request.Params["userrole"];
            List<User> users = getUsers();

            //ViewData["studentList"] = slist;

            string result = "<table><thead><th>Id</th><th>Role</th><th>Name</th><th>Age</th></thead>";

            foreach (User u in users)
            {
                if (u.Role.Contains(role))
                {
                    result += "<tr><td>" + u.UserId + "</td><td>" + u.Role + "</td><td>" + u.Name + "</td><td>" + u.Age + "</td><td></tr>";
                }
            }

            result += "</table>";
            return result;
        }

    }
}