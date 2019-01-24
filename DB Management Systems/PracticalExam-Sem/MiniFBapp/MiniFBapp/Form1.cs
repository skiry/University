using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace MiniFBapp
{
    public partial class Form1 : Form
    {
        SqlConnection dbConn;
        DataSet ds;
        SqlDataAdapter daUsers, daPosts;
        SqlCommandBuilder cb;
        BindingSource bsUsers, bsPosts;

        public Form1()
        {
            InitializeComponent();
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            daPosts.Update(ds, "Posts");
        }

        private void GetData()
        {
            dbConn = new SqlConnection(@"Data Source = LAPTOP-8A3HVFCJ\SQLEXPRESS; Initial Catalog = MiniFacebook; Integrated Security = SSPI");

            daUsers = new SqlDataAdapter("SELECT * FROM Users", dbConn);
            daPosts = new SqlDataAdapter("SELECT * FROM Posts", dbConn);

            cb = new SqlCommandBuilder(daPosts);

            ds = new DataSet();

            daUsers.Fill(ds, "Users");
            daPosts.Fill(ds, "Posts");

            ds.Relations.Add("FK_Posts_Users", ds.Tables["Users"].Columns["ID"], ds.Tables["Posts"].Columns["UserID"]);

            bsUsers = new BindingSource();
            bsUsers.DataSource = ds;
            bsUsers.DataMember = "Users";

            bsPosts = new BindingSource();
            bsPosts.DataSource = bsUsers;
            bsPosts.DataMember = "FK_Posts_Users";
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            GetData();
            dgvUsers.DataSource = bsUsers;
            dgvPosts.DataSource = bsPosts;
        }
    }
}
