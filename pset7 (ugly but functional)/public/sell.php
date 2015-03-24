<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via a redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("sell_form.php", ["title" => "Register"]);
    }
    
    // else if the user reached this via POST (by submitting form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
       $confirm = query("SELECT * FROM portfolio WHERE symbol = ?", $_POST["stockid"]);
       $checkprice = lookup($_POST["stockid"]);
       $price = number_format($checkprice["price"], 2) * $confirm[0]["shares"];
       
       if ($confirm == false)
       {
            apologize("You don't own that stock");
       }
       else
       {
            $sell = query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["stockid"]);
            $updatemoney = query("UPDATE users SET cash = cash + ? WHERE id = ?", $price, $_SESSION["id"]);
            $updateHistory = query("INSERT INTO history(symbol, shares, timestamp, action, id) VALUES(?, ?, CURRENT_TIMESTAMP, ?, ?)",
            $_POST["stockid"], $confirm[0]["shares"], "SELL", $_SESSION["id"]);
            
            redirect("index.php");
       }
       
    }
?>
