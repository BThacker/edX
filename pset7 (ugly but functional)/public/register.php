<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via a redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
    // else if the user reached this via POST (by submitting form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if ($_POST["username"] == "" || $_POST["password"] == "")
        {
            //apologize("You must enter a username and password");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("The passwords you entered did not match");
        } 
        else
        {
            $result = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
            
            if ($result === false)
            {
                apologize("Username probably already exists");
            }
            else
            {
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                if (count($rows) == 1)
                {
                $id = $rows[0]["id"];
                $_SESSION["id"] = $id;
                redirect("/");
                }
            }
        }
    }
?>
