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
function _acecrew_invoice_get_template_output($quote, $type=NULL) {
    ob_start();    

    $job = $quote['job'];
    $client = $quote['client'];
    $client_contact = $quote['client_contact'];
    $booked_by = $quote['job']->field_job_booked_by_value;
    $venue = $quote['venue'];
    $callings = $quote['callings'];

    $settings = db_fetch_object(db_query("SELECT * FROM {content_type_admin_settings}"));
    $footer_text = $settings->field_inv_footer_text_value;
    $footer_txt = explode("\r\n", $footer_text);

    $footer_content_s1 = isset($footer_txt[0]) ? $footer_txt[0] : "";
    $footer_content_s2 = isset($footer_txt[1]) ? $footer_txt[1] : "";
    $footer_content_s3 = isset($footer_txt[2]) ? $footer_txt[2] : "";
    $footer_content_s4 = isset($footer_txt[3]) ? $footer_txt[3] : "";
    $footer_content_s5 = isset($footer_txt[4]) ? $footer_txt[4] : "";
    
    $credit_image = drupal_get_path('module', 'acecrew') . '/theme/invoice-footer-credit.gif';
    //echo "<body>";
     

    $image = drupal_get_path('module', 'acecrew') . '/theme/acecrewquo.png';
  	$comp_address_1 = $client->field_client_company_address_value;
    $comp_address_2 = $client->field_client_company_postcode_value;

    $comp_address_1 = trim(preg_replace('/\s\s+/', ' ', $comp_address_1));
    $comp_address_1 = preg_replace('/\x03/', '', $comp_address_1);

    $venue_postcode = '';
    $venue_postcode = !empty($venue->field_venue_post_code_value) ? ' ('.$venue->field_venue_post_code_value.')' : '';

    $comp_address = nl2br($client->field_client_company_address_value);

    echo '<table class="acecrew_top_tbl" border=0 width=90% style="margin:0 auto;border-collapse:collapse;margin-top:30px;"><tr>';

    echo '<td>';
      echo '<table  width="200px" border=1 cellspacing=-1 cellpadding=5 align="left" style="margin-top:90px;border:0px solid;font-size:11px;">
        <tr><td>Invoice To:</td></tr>';
      echo '<tr><td><strong>'.$client->field_client_name_value.'</strong><br/>
            '.$comp_address.'
            <br/>'.$comp_address_2.'</td></tr>
            </table>';
    echo '</td>';

    echo '<td align="right" width="170px" style="">';
      echo '<img src=' . $image . ' height=220 alt=Acecrew style="text-align:right;" />';
      echo '<table style="width:170px;margin-top:20px;" border=1 cellspacing=-1 cellpadding=5 align="right" style="border:0px solid;">
        <tr><td width="50%">TAX DATE</td><td width="50%">Invoice NO.</td></tr>';
      echo '<tr><td>'.date("d/m/Y", $job->created).'</td><td>'._get_invoice_number($job->job_id).'</td></tr></table>';

      echo '<table style="width:170px;margin-top:20px;" border=1 cellspacing=-1 cellpadding=5 align="right" style="border:0px solid;">
        <tr><td width="50%">TERMS</td><td width="50%">ACE JOB NO.</td></tr>';
      echo '<tr><td>30 days</td><td>'.$job->job_id.'</td></tr></table>';
    echo '</td>';

    echo '</tr></table>';

    /*
    echo '
    <table class="acecrew_top_tbl" width=90% style="margin:0 auto;border:0px solid;border-collapse:collapse;">
    <tr>
    <td width=50%><h1 style="padding-top:75px;">' . t('Invoice') . ' - ' . _get_invoice_number($job->job_id) . '</h1></td>
    <td class=acecrew_logo>
        <img src=' . $image . ' width=270 height=220 alt=Acecrew style=margin-left:250px; />
    </td>
    </tr>
    <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    </tr>  
    </table>
    <hr width="95%" style="margin:0 auto;"/><br/><br/>
    <table width=90% border=1 cellspacing=-1 cellpadding=5 style="margin:0 auto;border:0px solid;border-collapse:collapse;">
    <tr>
        <td  style="font-weight:bold;">' . t('Client') . ':</td>
        <td>' . $client->field_client_name_value . '</td>
        <td style="font-weight:bold;"> ' . t('Purchase Order') . ':</td>
        <td> ' . $job->field_job_po_number_value . '</td>
        <td style="font-weight:bold;"> ' . t('Ace Job Reference') . ':</td>
        <td> ' . $job->job_id . ' </td>
    </tr>
    <tr> 
        <td style="font-weight:bold;">' . t('Address') . ':</td>
        <td colspan=5>' . $comp_address_1 . ', ' . $comp_address_2 . '</td>
    </tr>
    <tr> 
        <td style="font-weight:bold;">' . t('Booked by') . ':</td>
        <td colspan=2>' . $booked_by . '</td>
        <td style="font-weight:bold;">'. t('Date') .':</td>
        <td colspan=2>'. date("d/m/Y", $job->created) .'</td>
    </tr>
    </table><br/><br/>
    <table width=80% style="margin-left:40px;border:0px solid;border-collapse:collapse;">
    <tr>
        <td width=15% style="font-weight:bold;">' . t('Venue') . ': </td><td width=80% style="border-bottom:1px solid black;padding-left:10px;">' . $venue->field_venue_name_value . '</td>
    </tr>
    <tr>
        <td width=15% style="font-weight:bold;">' . t('Address') . ': </td><td width=80% style="border-bottom:1px solid black;padding-left:10px;">' . $venue->field_venue_address_value . '</td>
    </tr>
    <tr>
        <td width=15% style="font-weight:bold;">' . t('Postcode') . ': </td><td width=80% style="border-bottom:1px solid black;padding-left:10px;">' . $venue->field_venue_post_code_value . '</td>
    </tr>
    </table><br/><br/>';
    */
    $vat = NULL;
    $multiple_vat_values = FALSE;
    if (isset($invoice->invoice_items)) {
    foreach ($invoice->invoice_items as $item) {
      if (is_null($vat)) {
        $vat = $item['vat'];
      }

      if ($item['vat'] !== $vat) {
        $multiple_vat_values = TRUE;
      }
    }
    }
    
    $job_cancelation_status = 'Description';   

    echo '<table width=100% border=1 cellspacing=0 cellpadding=5 style="border:0px solid;border-collapse:collapse;margin: 0 30px;margin-top:40px;">';
    echo '<tr><td style="vertical-align:middle;" colspan=9>'.$job_cancelation_status.'</td><td width="5px">&nbsp;</td><td width="35px">Unit Price</td><td width="35px">Total</td></tr></table>';

    $call_index = 1;
    $sum = 0;
    foreach ($callings as $data) {
      echo '<div style="page-break-inside: avoid;"><table width="100%"  border=1 cellspacing=0 cellpadding=5 style="border:0px solid;border-collapse:collapse;margin: 0 30px;">';

      $call_amount = 0;
      $call = $data['data'];

      $call_number = explode('-', $call->field_session_callid_value);
      $call_number = $call_number[1];

      $venue = acecrew_get_venue_by_id($call->field_job_session_venue_value);
      $venue_name = $venue->field_venue_name[0]['value'];
      $venue_code = $venue->field_venue_post_code[0]['value'];
      if (!empty($venue_code)) {
        $venue_code = ' ('.$venue_code.')';
      }

      if ($call->field_job_session_plus_call_value === '1') {
        $call->field_job_session_hours_value = $call->field_job_session_hours_value.'+';
      } 

      // get call data from crew call table
      $call_data = _get_call_data($call);

      // date & time
      $date = substr($call->field_job_session_date_time_value, 0, 10);
      $time = substr($call->field_job_session_date_time_value, 11, 20);

      //watchdog('cc', '<pre>'.print_r($call->field_job_session_crew_value, TRUE).'</pre>');
      
      if (acecrew_is_cancellation_notice($call->cancellation_status) ||
          acecrew_is_cancellation_notice($job->cancellation_status)) {
        $number_of_standard_crews = $call->field_job_session_crew_value;
      } else {
        $number_of_standard_crews = count($call_data);          
      }            

      // quoted hours
      $quoted_hours = !empty($call->field_job_session_hours_value) ? $call->field_job_session_hours_value : '&nbsp;';

      $quoted_amount = _get_call_client_charge_amount($job, $client, $call);

      // additional hours, additional charges, and supplements
      $additional_hours = 0;
      $additional_charge = 0;
      $supplements = array();

      //Client total adjust
      $total_adjusted = false;
      $total_adjust_add = 0;
      $total_adjust_reduce = 0;
      
      foreach ($call_data as $dat) {
        $additional_hours += $dat->additional_hours;
        $additional_charge += $dat->additional_charge;

        //Total adjusted add
        $total_adjust_add += $dat->client_total_add;

        //Total adjusted reduce
        $total_adjust_reduce += $dat->client_total_reduce;

        // supplements data
        $uid = $dat->uid;
        $jsid = $dat->jsid;
        $query = "SELECT * FROM {crew_js_supplement} WHERE uid=$uid AND jsid=$jsid";
        $result = db_query($query);
        while ($row = db_fetch_object($result)) {
          $supp = node_load($row->supplement_id);
          $supplements[$row->supplement_id]['title'] = $supp->title;
          $supplements[$row->supplement_id]['quantity']++;          
          if ($row->client_ph != NULL) {
            $supplements[$row->supplement_id]['amount'] += $row->client_ph * ($call->field_job_session_hours_value + $dat->additional_hours);
            $call_amount += $row->client_ph * ($call->field_job_session_hours_value + $dat->additional_hours);
          } else {
            $supplements[$row->supplement_id]['amount'] += $row->client_of;
            $call_amount += $row->client_of;
          }
          //$call_amount += $supplements[$row->supplement_id]['amount'];
        }
      }
      // add additional charge
      $inc = 1;
      if ($additional_charge > 0) {
        $call_amount += $additional_charge;
        $inc++;
      }

      $client_rate = $call->field_job_session_client_rate_value == NULL ? 1 : $call->field_job_session_client_rate_value;
      // call amount
      $call_amount += $quoted_amount * $number_of_standard_crews;
      $call_amount += $client_rate * $additional_hours;
      // add call amount

      //Client additional charge amount
      $additional_client_charge = (float) $call->field_additional_charge_ammount_value;
      $additional_client_desc = $call->field_additional_charge_desc_value;

      if ($additional_client_charge >= 1) $inc++;
      $call_amount += $additional_client_charge;

      //Client discount
      $discount = (float) $job->field_job_discount_value;
      $discount_desc = $job->field_job_discount_desc_value;

      // boundary charge
      $boundary_charge = 0;
      if ($call->field_add_boundary_charge_value == 1) {
        $boundary_charge = $call->field_session_boundary_charge_value * $number_of_standard_crews;
        $inc++;
      }
      $call_amount += $boundary_charge;
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

      $call_amount += $mileage_charge;

      //If client total is adjusted, adjust the $call_amount
      if($total_adjust_add || $total_adjust_reduce) {
          $call_amount = $call_amount + $total_adjust_add - $total_adjust_reduce;
          $total_adjusted = true;
      } 

      if ($call->cancellation_status == CANCELLATION_NORMAL ||
        ($job->cancellation_status == CANCELLATION_NORMAL &&
        $call->cancellation_status == CANCELLATION_NA)) {
        $call_amount = 0;
      }
      $sum += acecrew_cancellation_price_total($call_amount, 
                                               $call->cancellation_status, 
                                               $job->cancellation_status);

      if ($additional_hours > 0) $inc++;
      
      $call_cancelation_status = '';
    
      echo '
        <tr>
          <td rowspan=' . (count($supplements) + $inc) . ' valign=top style="font-weight:bold;">Call: ' . $call_number . '. @ '. $venue_name . $venue_code . $call_cancelation_status . '</td>
          <td width="10px" valign=top>Date: </td>
          <td width="45px" valign=top>' . $date . '</td>
          <td width="10px" valign=top>Time: </td>
          <td width="5px" valign=top>' . $time . '</td>
          <td width="10px" valign=top>Crew: </td>
          <td width="8px" valign=top>' . $number_of_standard_crews . '</td>
          <td width="10px" valign=top>Hours: </td>
          <td width="12px" valign=top>' . $quoted_hours . '</td>
          <td width="5px" valign=top>=</td>
          <td width="35px" valign=top>' . ($total_adjusted ? "" : '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($quoted_amount, 'unit_price', $call->cancellation_status, $job->cancellation_status)) ) . '</td>
          <td width="35px" valign=top>&pound;' . ($total_adjusted ? sprintf("%01.2f", acecrew_cancellation_price($quoted_amount * $number_of_standard_crews + $total_adjust_add - $total_adjust_reduce, $call->cancellation_status, $job->cancellation_status)) : sprintf("%01.2f", acecrew_cancellation_price($quoted_amount * $number_of_standard_crews, 'total', $call->cancellation_status, $job->cancellation_status)) ) . '</td>
        </tr>';
        if ($additional_hours > 0) {
          echo "<tr>
                <td colspan=8 valign=top>Includes $additional_hours additional hours</td>
                <td valign=top width='5px'>&#xd7;</td>
                <td valign=top width='35px'>&pound;" . sprintf("%01.2f", acecrew_cancellation_price($client_rate, 'unit_price', $call->cancellation_status)) . "</td>
                <td valign=top width='35px'>&pound;" . sprintf("%01.2f", acecrew_cancellation_price($client_rate * $additional_hours, 'total', $call->cancellation_status)) . "</td>
              </tr>";
        }
        if ($call->field_add_boundary_charge_value == 1) {
          echo '
            <tr>
                <td colspan=4 valign=top>Boundary Charge:</td>
                <td colspan=4 valign=top>' . $call->field_job_session_crew_value . '</td>
                <td valign=top width="5px">&#xd7;</td>
                <td valign=top width="35px">&pound;' . sprintf("%01.2f", acecrew_cancellation_price(get_default_boundary_charge(), 'unit_price', $call->cancellation_status, $job->cancellation_status)) . '</td>
                <td valign=top width="35px">&pound;' . sprintf("%01.2f", acecrew_cancellation_price($boundary_charge, 'total', $call->cancellation_status, $job->cancellation_status)) . '</td>
            </tr>';
        }
      if ($call->field_session_num_vehicles_value >= 1) {
          echo '
            <tr>
                <td colspan=4 valign=top>Mileage Charge(' . $distance . ' miles): </td>
                <td colspan=4 valign=top>' . $call->field_session_num_vehicles_value . '</td>
                <td valign=top width="5px">&#xd7;</td>
                <td valign=top width="35px">&pound;' . sprintf("%01.2f", acecrew_cancellation_price($mileage_unit, 'unit_price', $call->cancellation_status, $job->cancellation_status)) . '</td>
                <td valign=top width="35px">&pound;' . sprintf("%01.2f", acecrew_cancellation_price($mileage_charge, 'total', $call->cancellation_status, $job->cancellation_status)) . '</td>
            </tr>';
        }

        if ($additional_client_charge >= 1) {
            echo '
            <tr>
                <td colspan=2 valign=top>Additional Charges: </td>
                <td colspan=6 valign=top>' . $additional_client_desc . '</td>
                <td width="5px" valign=top>=</td>
                <td width="35px" valign=top>&nbsp;</td>
                <td valign=top width="35px">&pound;' . sprintf("%01.2f", acecrew_cancellation_price($additional_client_charge, 'total', $call->cancellation_status, $job->cancellation_status)) . '</td>
            </tr>';
        }        
        foreach ($supplements as $supplement) {
//            $sum += $supplement['amount'];
            if($supplement['amount']) {
                echo '
                <tr>
                    <td colspan=4 valign=top>' . $supplement['title'] . ':</td>
                    <td colspan=4 valign=top>' . $supplement['quantity'] . '</td>
                    <td valign=top width="5px">&#xd7;</td>
                    <td valign=top width="35px">&nbsp;</td>
                    <td valign=top width="35px">&pound;' . sprintf("%01.2f", acecrew_cancellation_price($supplement['amount'], 'total', $call->cancellation_status, $job->cancellation_status)) . '</td>
                </tr>';
            }  else {
                echo '<tr><td colspan=11></td></tr>';
            }
        }
//        $sum += $additional_charge;
        if ($additional_charge != 0) {
            echo '<tr>
                    <td colspan=8 valign=top>Additional costs: </td>
                    <td colspan=2 width="5px" valign=top>=</td>
                    <td valign=top width="35px">&pound;' . sprintf("%01.2f", acecrew_cancellation_price($additional_charge, 'total', $call->cancellation_status, $job->cancellation_status)) . '</td>
                </tr>';
        }
        echo "</table></div>";
        $call_index++;
    }

    
    //echo '<div style="page-break-inside: avoid;"><table width=100% border=1 cellspacing=0 cellpadding=5 style="page-break-inside: avoid; border:0px solid;border-collapse:collapse;margin: 0 30px;"><tr><td colspan="12" align="left">NOTES:&nbsp;'.$job->field_invoice_notes_value.'</tr></table></div>';

    if ($discount >= 1) {        
        echo '<div style="page-break-inside: avoid;"><table width=100% border=1 cellspacing=0 cellpadding=5 style="page-break-inside: avoid; border:0px solid;border-collapse:collapse;margin: 0 30px;"><tr>
                <td colspan=1 valign=top>Discount: </td>
                <td colspan=10 valign=top>' . $discount_desc . '</td>
                <td valign=top width="35px">- &pound;' . sprintf("%01.2f", acecrew_cancellation_price($discount, 'discount', $call->cancellation_status, $job->cancellation_status)) . '</td>
            </tr></tr></table></div>';
    }    
    $sum -= $discount;

    $vat = round(getVAT() * $sum / 100, 2);    

    echo '<div style="page-break-inside: avoid;"><table width=100% border=1 cellspacing=0 cellpadding=5 style="page-break-inside: avoid; border:0px solid;border-collapse:collapse;margin: 0 30px;"><tr><td colspan="11" align="right">Total (Excluding VAT)</td><td width="35px">&pound;' . sprintf("%01.2f", acecrew_cancellation_price($sum, 'excluding_vat')) . '</td></tr></table></div>';
    echo '<div style="page-break-inside: avoid;"><table width=100% border=1 cellspacing=0 cellpadding=5 style="page-break-inside: avoid; border:0px solid;border-collapse:collapse;margin: 0 30px;"><tr><td colspan="11" align="right">+ VAT</td><td width="35px">&pound;' . sprintf("%01.2f", acecrew_cancellation_price($vat, 'vat')) . '</td></tr></table></div>';
    echo '<div style="page-break-inside: avoid;"><table width=100% border=1 cellspacing=0 cellpadding=5 style="page-break-inside: avoid; border:0px solid;border-collapse:collapse;margin: 0 30px;"><tr><td colspan="11" align="right">TOTAL</td><td width="35px">&pound;' . sprintf("%01.2f", acecrew_cancellation_price($sum + $vat, 'including_vat')) . '</td></tr></table></div>';

    $notes_tr = empty($job->field_invoice_notes_value) ? '' : '<tr><td colspan="12" align="left"><span style="color:#f00;">'.$job->field_invoice_notes_value.'</span></td></tr>';

    echo '<table width="370px" border=1 cellspacing=-1 cellpadding=5 align="left" style="margin-top:5px;margin-left:30px;border:0px solid;font-size:11px;">
        '.$notes_tr.'
        <tr><td colspan="6" align="center" valign=middle><img src=' . $credit_image . ' height=220 alt=Acecrew style="text-align:center;vertical-align: middle;" /></td><td colspan="6">BACS details:<br/>
Account Name: Ace Crew Ltd<br/>
Account Number: 30724459<br/>
Sort Code: 20-96-55<br/>
IBAN: GB18BARC20965530724459<br/>
SWIFT: BARCGB22</td></tr>
    <tr><td colspan="6">VAT Reg No: 918965374<br/>
Company No: 06128298</td><td colspan="6">Ace Crew Ltd<br/>
Unit 6 Princess Court, Horace Road,<br/> Kingston Upon Thames, KT1 2SL</td></tr>
      </table>';


    /*
    echo '<div style="width: 20px; height: 120px;"></div>';
     
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
          
        $offset = 125;

        $pdf->line(40, $h-$offset, $w-40, $h-$offset, $a_line_color, 1, array()); 
          
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

        $pdf->text(($w - $footer_content_s1_len) / 2, $h - $offset + $footer_content_font_space, $footer_content_s1, $font, $footer_content_font_size, $a_text_color);
        $pdf->text(($w - $footer_content_s2_len) / 2, $h - $offset + $footer_content_font_space*2 + $footer_content_font_size, $footer_content_s2, $font, $footer_content_font_size, $a_text_color);
        $pdf->text(($w - $footer_content_s3_len) / 2, $h - $offset + $footer_content_font_space*3 + $footer_content_font_size*2, $footer_content_s3, $font, $footer_content_font_size, $a_text_color);
        $pdf->text(($w - $footer_content_s4_len) / 2, $h - $offset + $footer_content_font_space*4 + $footer_content_font_size*3, $footer_content_s4, $font, $footer_content_font_size, $a_text_color);
        $pdf->text(($w - $footer_content_s5_len) / 2, $h - $offset + $footer_content_font_space*5 + $footer_content_font_size*4, $footer_content_s5, $font, $footer_content_font_size, $a_text_color);
        
        $pdf->image("'.$credit_image.'", "gif", (($w - $footer_content_s5_len) / 2) + 20, $h - $offset + 20 + $footer_content_font_space + $footer_content_font_size*4, 162, 64);

        $pdf->page_text($w-27, $h-27, "{PAGE_NUM}/{PAGE_COUNT}", $font, 10, $a_text_color);
                                                                              
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
    */     

    $content = ob_get_contents(); ob_end_clean();
    return $content;
}

function is_exist_allocated_supplement($call_id, $supp_id) {
    $allocated_supplement = array();

    $query = "SELECT * FROM {crew_js_supplement} WHERE jsid = %s AND supplement_id = %s";
    $result = db_query($query, $call_id, $supp_id);
    while($row = db_fetch_object($result)) {
        $allocated_supplement[] = $row;
    }

    return count($allocated_supplement) > 0 ? $allocated_supplement : FALSE;
}