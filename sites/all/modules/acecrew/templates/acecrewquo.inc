<?php
// $Id: acecrewquo.inc,v 1.1.2.2 2009/01/02 21:24:23 pvogelaar Exp $

/**
 * @file
 * Invoice module
 *
 * This module was developed by Platina Designs, http://www.platinadesigns.nl
 *
 * @author Pieter Vogelaar <ps.vogelaar@platinadesigns.nl>
 */

/**
 * Function to create the invoice layout
 *
 * Documentation available at:
 * - http://www.digitaljunkies.ca/dompdf/faq.php
 * - http://www.digitaljunkies.ca/dompdf/usage.php
 */
function _acecrew_quote_get_template_output($quote, $type=NULL) {
    ob_start();

    $job = $quote['job'];
    $client = $quote['client'];
    $client_contact = $quote['client_contact'];
    $booked_by = $quote['job']->field_job_booked_by_value;
    $venue = $quote['venue'];
    $callings = $quote['callings'];

    /*
      // Create alias
      $template =& $invoice->invoice['template'];

      // Set full url path to template
      $path_to_template = 'http://'. $_SERVER['HTTP_HOST'] . base_path() . path_to_theme('module', 'invoice') .'/templates';

      if ($type != 'pdf') {
        $s_pagenum = '1/1';
      }
      else {
        $s_pagenum = '';
      }

      //fix encoding problem when convert GBP character to HTML entites
      foreach ($invoice->invoice as $key => $value){
        if(!is_array($value)){
          $invoice->invoice[$key] = str_replace('&Acirc;', '', htmlentities($value));
        }

      }
    */

    $settings = db_fetch_object(db_query("SELECT * FROM {content_type_admin_settings}"));
    $footer_text = $settings->field_quo_footer_text_value;
    $footer_txt = explode("\r\n", $footer_text);

    $footer_content_s1 = isset($footer_txt[0]) ? $footer_txt[0] : "";
    $footer_content_s2 = isset($footer_txt[1]) ? $footer_txt[1] : "";
    $footer_content_s3 = isset($footer_txt[2]) ? $footer_txt[2] : "";
    $footer_content_s4 = isset($footer_txt[3]) ? $footer_txt[3] : "";
    $footer_content_s5 = isset($footer_txt[4]) ? $footer_txt[4] : "";

    if ($type == 'pdf') {
        $footer = '<script type="text/php">
                if (isset($pdf)) {
                  $footer = $pdf->open_object();

                  $w = $pdf->get_width();
                  $h = $pdf->get_height();

                  $font = Font_Metrics::get_font("arial");

                  $r=128; $g=128; $b=128;

                  $a_line_color = array(0 => $r / 0xff, 1 => $g / 0xff, 2 => $b / 0xff,
                    "r"=>$r / 0xff, "g"=>$g / 0xff, "b"=>$b / 0xff,
                    "hex" => sprintf("#%02X%02X%02X", $r, $g, $b));

                  $a_text_color = array(0 => $r / 0xff, 1 => $g / 0xff, 2 => $b / 0xff,
                    "r"=>$r / 0xff, "g"=>$g / 0xff, "b"=>$b / 0xff,
                    "hex" => sprintf("#%02X%02X%02X", $r, $g, $b));

                  $pdf->line(40, $h-60, $w-40, $h-60, $a_line_color, 1, array());

                  $footer_content_font_size = 8;
                  $footer_content_font_space = 1;

                  $footer_content_s1 = \'' . $footer_content_s1 . '\';
                  $footer_content_s2 = \'' . $footer_content_s2 . '\';
                  $footer_content_s3 = \'' . $footer_content_s3 . '\';
                  $footer_content_s4 = \'' . $footer_content_s4 . '\';
                  $footer_content_s5 = \'' . $footer_content_s5 . '\';


                  $footer_content_s1_len  = $pdf->get_text_width($footer_content_s1, $font, $footer_content_font_size);
                  $footer_content_s2_len  = $pdf->get_text_width($footer_content_s2, $font, $footer_content_font_size);
                  $footer_content_s3_len  = $pdf->get_text_width($footer_content_s3, $font, $footer_content_font_size);
                  $footer_content_s4_len  = $pdf->get_text_width($footer_content_s4, $font, $footer_content_font_size);
                  $footer_content_s5_len  = $pdf->get_text_width($footer_content_s5, $font, $footer_content_font_size);

                  $pdf->text(($w - $footer_content_s1_len) / 2, $h - 60 + $footer_content_font_space, $footer_content_s1, $font, $footer_content_font_size, $a_text_color);
                  $pdf->text(($w - $footer_content_s2_len) / 2, $h - 60 + $footer_content_font_space*2 + $footer_content_font_size, $footer_content_s2, $font, $footer_content_font_size, $a_text_color);
                  $pdf->text(($w - $footer_content_s3_len) / 2, $h - 60 + $footer_content_font_space*3 + $footer_content_font_size*2, $footer_content_s3, $font, $footer_content_font_size, $a_text_color);
                  $pdf->text(($w - $footer_content_s4_len) / 2, $h - 60 + $footer_content_font_space*4 + $footer_content_font_size*3, $footer_content_s4, $font, $footer_content_font_size, $a_text_color);
                  $pdf->text(($w - $footer_content_s5_len) / 2, $h - 60 + $footer_content_font_space*5 + $footer_content_font_size*4, $footer_content_s5, $font, $footer_content_font_size, $a_text_color);

                  $pdf->page_text($w-57, $h-39, "{PAGE_NUM}/{PAGE_COUNT}", $font, 10, $a_text_color);

                  $pdf->close_object();

                  $pdf->add_object($footer, "all");
                }
                </script>';
        echo $footer;
        $footer = '';
    }
    else {
        $footer = $footer_content;
    }

    $image = drupal_get_path('module', 'acecrew') . '/theme/acecrewquo.png';

    echo '
  <table class="acecrew_top_tbl" width=90% style="margin:0 auto;border:0px solid;border-collapse:collapse;">
  <tr>
    <td style="width:390px;"><h1 style="padding-top:75px;">Quote - ' . $quote['job']->field_job_number_value . '</h1></td>
    <td>
        <img src=' . $image . ' width=270 height=220 alt="Acecrew" style="margin-left:0px;" />
    </td>
  </tr>
  </table>
  <br/><br/>
  <hr width="95%" style="margin:0 auto;"/><br/><br/>
  <table width=90% border=1 cellspacing=-1 cellpadding=5 style="margin:0 auto;border:0px solid;border-collapse:collapse;">
    <tr>
        <td width=30% style="font-weight:bold;">' . t('Client') . ':</td>
        <td width=70%>' . $client->field_client_name_value . '</td>
        <td width=30% style="font-weight:bold;"> ' . t('Reference') . ':</td>
        <td width=70%> ' . $job->job_id . ' </td>
    </tr>
    <tr>
        <td style="font-weight:bold;">' . t('Booked by') . ':</td>
        <td>' . $booked_by . '</td>
        <td style="font-weight:bold;">'. t('Date') .':</td>
        <td>'. date("d/m/Y", $job->created) .'</td>
    </tr>
  </table><br/><br/>
  <table width=80% style="margin-left:40px;border:0px solid;border-collapse:collapse;">
    <tr>
        <td width=15% style="font-weight:bold;">' . t('Venue') . ': </td><td width=80% style="border-bottom:1px solid black;padding-left:10px;">' . $venue->field_venue_name_value . '</td>
    </tr>
    <tr>
        <td width=15% style="font-weight:bold;">' . t('Adress') . ': </td><td width=80% style="border-bottom:1px solid black;padding-left:10px;">' . $venue->field_venue_address_value . '</td>
    </tr>
    <tr>
        <td width=15% style="font-weight:bold;">' . t('Postcode') . ': </td><td width=80% style="border-bottom:1px solid black;padding-left:10px;">' . $venue->field_venue_post_code_value . '</td>
    </tr>
  </table><br/><br/>';

    /*$vat = NULL;
    $multiple_vat_values = FALSE;
    foreach ($invoice->invoice_items as $item) {

      if (is_null($vat)) {
        $vat = $item['vat'];
      }

      if ($item['vat'] !== $vat) {
        $multiple_vat_values = TRUE;
      }
    }*/

    echo '<table width=90% border=1 cellspacing=0 cellpadding=5 style="margin-bottom:120px;border:0px solid;border-collapse:collapse;margin-left:5%;">';
    echo '<tr><td colspan=9></td><td>&nbsp;</td><td>Unit Price</td><td>Total</td></tr>';
    $call_index = 1;
    $sum = 0;
    foreach ($callings as $data) {
        $call = $data['data'];
        $supplements = $data['supplements'];
        $call_amount = _get_call_client_charge_amount($job, $client, $call);
        $total = $call_amount * $call->field_job_session_crew_value;

        //Client additional charge amount
        $additional_client_charge = (float) $call->field_additional_charge_ammount_value;
        $additional_client_desc = $call->field_additional_charge_desc_value;

        //Client discount
        $discount = (float) $job->field_job_discount_value;
        $discount_desc = $job->field_job_discount_desc_value;

        $boundary_charge = 0;
        $inc = 1;

        if ($additional_client_charge >= 1) $inc++;

        // boundary charge
        if ($call->field_add_boundary_charge_value == 1) {
            $boundary_charge = $call->field_session_boundary_charge_value * $call->field_job_session_crew_value;
            $inc++;
        }

        // mileage charge
        $mileage_charge = 0;
        $mileage_unit = 0;

        //Venue distance
        $venue_mileage = (int) acecrew_get_venue_milage_by_venue_id($call->field_job_session_venue_value);

        if($venue_mileage) {
            $distance = $venue_mileage;
        } else {
            $distance = 0;
        }

        //If vehicles are assigned to call
        if ($call->field_session_num_vehicles_value >= 1) {
            //Set mileage unit
            $mileage_unit = $call->field_job_session_mileage_value;
            //Calculate charge per miles, distance * num of vehicles * charge per mile
            $mileage_charge =  $distance * $call->field_session_num_vehicles_value * $mileage_unit;
            $inc++;
        }

        echo '
        <tr>
            <td width=13% rowspan=' . (count($supplements) + $inc) . ' valign=top style="font-weight:bold;">Call: ' . ($call_index) . '</td>
            <td width=4% valign=top>Date: </td>
            <td width=10% valign=top>' . substr($call->field_job_session_date_time_value, 0, 10) . '</td>
            <td width=4% valign=top>Time: </td>
            <td width=10% valign=top>' . substr($call->field_job_session_date_time_value, 11, 20) . '</td>
            <td width=4% valign=top>Crew: </td>
            <td width=10% valign=top>' . $call->field_job_session_crew_value . '</td>
            <td width=4% valign=top>Hours: </td>
            <td width=10% valign=top>' . $call->field_job_session_hours_value . '</td>
            <td width=2% valign=top>=</td>
            <td width=7% valign=top>&pound;' . sprintf("%01.2f", $call_amount) . '</td>
            <td width=7% valign=top>&pound;' . sprintf("%01.2f", $total) . '</td>
        </tr>';

        if ($call->field_add_boundary_charge_value == 1) {
            echo '
            <tr>
                <td colspan=4 valign=top>Boundary Charge:</td>
                <td colspan=4 valign=top>' . $call->field_job_session_crew_value . '</td>
                <td valign=top>&#xd7;</td>
                <td valign=top>' . get_default_boundary_charge() . '</td>
                <td valign=top>&pound;' . sprintf("%01.2f", $boundary_charge) . '</td>
            </tr>';
        }
        if ($call->field_session_num_vehicles_value >= 1) {
            echo '
            <tr>
                <td colspan=4 valign=top>Mileage Charge(' . $distance . ' miles): </td>
                <td colspan=4 valign=top>' . $call->field_session_num_vehicles_value . '</td>
                <td valign=top>&#xd7;</td>
                <td valign=top>' . $mileage_unit . '</td>
                <td valign=top>&pound;' . sprintf("%01.2f", $mileage_charge) . '</td>
            </tr>';
        }

        if ($additional_client_charge >= 1) {
            echo '
            <tr>
                <td colspan=2 valign=top>Additional Charges: </td>
                <td colspan=6 valign=top>' . $additional_client_desc . '</td>
                <td width=2% valign=top>=</td>
                <td width=7% valign=top>&nbsp;</td>
                <td valign=top>&pound;' . $additional_client_charge . '</td>
            </tr>';
        }

        $total += $additional_client_charge;
        $total += $boundary_charge;
        $total += $mileage_charge;
        $sum += $total;

        foreach($supplements as $supplement) {
            $node = node_load($supplement->field_call_supplements_nid);
            $quantity = explode("\"", $supplement->field_call_supplements_fields);
            $quantity = $quantity[3];
            $quantity = $quantity == NULL ? 1 : $quantity;

            /**
             * Set default supplement price based on quoted hours
             */
            if($call->field_job_session_hours_value <= 4) {
                //hours 0-4
                $hp = $node->field_supp_0to4_client_hour[0]['value'];
                $op = $node->field_supp_0to4_client_single[0]['value'];

            } else if ($call->field_job_session_hours_value <= 8) {
                //hours 5-8
                $hp = $node->field_supp_5to8_client_hour[0]['value'];
                $op = $node->field_supp_5to8_client_single[0]['value'];

            } else if ($call->field_job_session_hours_value <= 12) {
                //hours 8-12
                $hp = $node->field_supp_9to12_client_hour[0]['value'];
                $op = $node->field_supp_9to12_client_single[0]['value'];
            } else {
                //hours 12+
                $hp = $node->field_supp_12plus_client_hour[0]['value'];
                $op = $node->field_supp_12plus_client_single[0]['value'];
            }

            $is_hourly = $hp != NULL ? true : false;
            if($is_hourly) {
                $value = $hp * $quantity * $call->field_job_session_hours_value;
            } else {
                $value = $op * $quantity;
            }
            if($value) {
                echo '
                <tr>
                    <td colspan=4 valign=top>' . $node->title . ':</td>
                    <td colspan=4 valign=top>' . $quantity . '</td>
                    <td valign=top>&nbsp;</td>
                    <td valign=top>&nbsp;</td>
                    <td valign=top>&pound;' . sprintf("%01.2f", $value) . '</td>
                </tr>';
            } else {
                echo '<tr><td colspan=11></td></tr>';
            }

            $sum += $value;
        }
        $call_index++;
  }

    if ($discount >= 1) {
        echo '
            <tr>
                <td colspan=1 valign=top>Discount: </td>
                <td colspan=8 valign=top>' . $discount_desc . '</td>
                <td valign=top>&nbsp;</td>
                <td valign=top>&nbsp;</td>
                <td valign=top>- &pound;' . sprintf("%01.2f", $discount) . '</td>
            </tr>';
    }

    $sum -= $discount;

    $vat = round(getVAT() * $sum / 100, 2);

  echo '<tr><td colspan="11" align="right">Total (Excluding VAT)</td><td>&pound;'. sprintf("%01.2f", $sum) .'</td></tr>';
  echo '<tr><td colspan="11" align="right">+ VAT</td><td>&pound;' . sprintf("%01.2f", $vat) . '</td></tr>';
  echo '<tr><td colspan="11" align="right">TOTAL</td><td>&pound;' . sprintf("%01.2f", $sum + $vat) . '</td></tr>';

  echo '</table>';

  $content = ob_get_contents(); ob_end_clean();
  return $content;
}

function getVAT() {
    $vat = 0;
    $query = "SELECT field_admins_vatrate_value FROM {content_type_admin_settings}";
    $result = db_query($query);
    while($row = db_fetch_object($result)) {
        $vat = $row->field_admins_vatrate_value;
    }

    return $vat == 0 ? 20 : $vat;
}
