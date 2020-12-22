var sql = require("mssql");

// Create a configuration object for our Azure SQL connection parameters
var dbConfig = {
 server: "program.database.windows.net", // Use your SQL server name
 database: "program", // Database to connect to
 user: "mihai", // Use your username
 password: "paunescu69?", // Use your password
 port: 1433,
 // Since we're on Windows Azure, we need to set the following options
 options: {
       encrypt: true
   }
};
var a=10;
// This function connects to a SQL server, executes a SELECT statement,
// and displays the results in the console.
async function getCustomers() {
 // Create connection instance
 var conn = new sql.ConnectionPool(dbConfig);

 conn.connect()
 // Successfull connection

 .then(function () {

   // Create request instance, passing in connection instance
   var req = new sql.Request(conn);
   var username="a@a";
   var parola="a";
   // Call mssql's query method passing in params
 await  req.query( "Select * from utilizatori where (username='"+username+"' and parola='"+parola+"');")
   .then(async function (recordset) {
    // console.log(recordset.rowsAffected);
    

  
    conn.close();
   
    a= 1;
   })
   // Handle sql statement execution errors
   .catch(function (err) {
     console.log(err);
     
     conn.close();
   })

 })
 // Handle connection errors
 .catch(function (err) {
   console.log(err);
   conn.close();
 });
 //a= 0;
}

async function fd(){
 var b=await getCustomers();

 console.log("  dddd  %d",a);

}
 fd();