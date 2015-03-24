<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via a redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("addfunds_form.php", ["title" => "Add Funds"]);
    }
    
    // else if the user reached this via POST (by submitting form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
       $addfunds = query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["addfunds"], $_SESSION["id"]);
       redirect("index.php");
    }
?>
