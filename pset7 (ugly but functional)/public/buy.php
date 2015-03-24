<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via a redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Register"]);
    }
    
    // else if the user reached this via POST (by submitting form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
       $confirm = lookup($_POST["stockid"]);
       $price = number_format($confirm["price"], 2) * $_POST["share"];
       
       if ($confirm == false)
       {
            apologize("That stock doesn't exist");
       }
       else
       {
            $buy = query("INSERT INTO portfolio (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
            $_SESSION["id"], $_POST["stockid"], $_POST["share"]);
            $updateCash = query("UPDATE users SET cash = cash - ? WHERE id = ?", $price, $_SESSION["id"]); 
            $updateHistory = query("INSERT INTO history(symbol, shares, timestamp, action, id) VALUES(?, ?, CURRENT_TIMESTAMP, ?, ?)",
            $_POST["stockid"], $_POST["share"], "BUY", $_SESSION["id"]);
            
            redirect("index.php");
       }
       
    }
?>
