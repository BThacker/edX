
<div>
    <h3>Stock Quote</h3> </br>
    
<?php
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        if ($stock == false)
        {
            print("Invalid Stock ID");
        }
        else
        {
            $formatNum = number_format($stock["price"], 2);
            print("Symbol: " . $stock["symbol"]);
            print("</br>");
            print("Name: " . $stock["name"]);
            print("</br>");
            print("Price: " . $formatNum);
            print("</br>");
        }
    }
?>
</div>
