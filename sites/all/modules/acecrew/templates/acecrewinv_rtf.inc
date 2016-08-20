<?php

function _acecrew_invoice_get_template_output($quote, $type=NULL) {
    global $base_url;

    $job = $quote['job'];
    $client = $quote['client'];
    $client_contact = $quote['client_contact'];
    $booked_by = $quote['job']->field_job_booked_by_value;
    $venue = $quote['venue'];
    $callings = $quote['callings'];

    $logo = dirname(__FILE__) . '/../theme/acecrewquo.png';

    PHPRtfLite::registerAutoloader();

    $rtf = new PHPRtfLite();
    //Set page margins
    $rtf->setMargins(1, 0.6, 1, 0); // 1, 0.6, 1, 0

    $section = $rtf->addSection();
    //$section->setPaperWidth(18);
    
    $border_header = new PHPRtfLite_Border(
        $rtf,                                       // PHPRtfLite instance
        new PHPRtfLite_Border_Format(1, '#fff'), // left border: 2pt, green color
        new PHPRtfLite_Border_Format(1, '#fff'), // top border: 1pt, yellow color
        new PHPRtfLite_Border_Format(1, '#fff'), // right border: 2pt, red color
        new PHPRtfLite_Border_Format(1, '#000')  // bottom border: 1pt, blue color
    );
    //Style quote table
    $border = new PHPRtfLite_Border(
        $rtf,                                       // PHPRtfLite instance
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c'), // left border: 2pt, green color
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c'), // top border: 1pt, yellow color
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c'), // right border: 2pt, red color
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c')  // bottom border: 1pt, blue color
    );
    //Style quote table
    $border_table = new PHPRtfLite_Border(
        $rtf,                                       // PHPRtfLite instance
        new PHPRtfLite_Border_Format(0.5, '#8c8c8c'), // left border: 2pt, green color
        new PHPRtfLite_Border_Format(0.5, '#8c8c8c'), // top border: 1pt, yellow color
        new PHPRtfLite_Border_Format(0.5, '#8c8c8c'), // right border: 2pt, red color
        new PHPRtfLite_Border_Format(0.5, '#8c8c8c')  // bottom border: 1pt, blue color
    );

    $bold = new PHPRtfLite_Font(10);
    $bold->setBold();
    $small_font = new PHPRtfLite_Font(10);

    //Set top table
    $table = $section->addTable();
    //Add 3 row
    $table->addRows(8, 0.5);
    $table->addColumnsList(array(6,4.85,4,4));
    //$table->mergeCellRange(2,1,5,1);
    $font_normal = new PHPRtfLite_Font(12, 'arial', '#000');
    $table->writeToCell(1,1, 'Invoice To:', $font_normal); 
    $table->getCell(1,1)->setCellPaddings(0.1,0.1,0.1,0.1);
    $font = new PHPRtfLite_Font(12, 'arial', '#000');
    $font->setBold();
    $table->writeToCell(2,1, $client->field_client_name_value, $font);
    $table->getCell(2,1)->setCellPaddings(0.1,0.1,0.1,0.1);
    $font = new PHPRtfLite_Font(12, 'arial', '#000');
    $table->writeToCell(2,1, '<br>'.$client->field_client_company_address_value, $font);
    $table->writeToCell(2,1, '<br>'.$client->field_client_company_postcode_value, $font);
    $table->setBorderForCellRange($border_table,1,1);
    $table->setBorderForCellRange($border_table,2,1); 

    if (!empty($job->field_job_po_number_value)) {
        $font_normal = new PHPRtfLite_Font(12, 'arial', '#000');
        $table->writeToCell(4,1, 'Purchase Order:', $font_normal);
        $table->getCell(4,1)->setCellPaddings(0.1,0.1,0.1,0.1);
        $table->setBorderForCellRange($border_table,4,1);        
        $table->writeToCell(5,1, $job->field_job_po_number_value, $font_normal);     
        $table->getCell(5,1)->setCellPaddings(0.1,0.1,0.1,0.1);
        $table->setBorderForCellRange($border_table,5,1);
    }

    // image cell
    $table->mergeCellRange(1,3,2,4);    
    //$table->mergeCellRange(2,3,2,4);    
    $cell = $table->getCell(1,3);
    $cell->setCellPaddings(0,0,0,0); //
    $cell->setCellPaddings(3,0,0,0);
    $image = $cell->addImage($logo);
    $image->setWidth(5);
    $image->setHeight(3.5);
    //
    $font = new PHPRtfLite_Font(12, 'arial', '#000');
    $table->writeToCell(4,3, 'TAX DATE', $font);
    $table->getCell(4,3)->setCellPaddings(0.1,0.1,0.1,0.1);
    $table->setBorderForCellRange($border_table,4,3);
    $table->writeToCell(4,4, 'Invoice NO.', $font);
    $table->getCell(4,4)->setCellPaddings(0.1,0.1,0.1,0.1);
    $table->setBorderForCellRange($border_table,4,4);
    $table->writeToCell(5,3, date("d/m/Y", $job->created), $font);
    //
    $table->getCell(5,3)->setCellPaddings(0.1,0.1,0.1,0.1);
    $table->setBorderForCellRange($border_table,5,3);
    $table->writeToCell(5,4, _get_invoice_number($job->job_id), $font);
    //
    $table->getCell(5,4)->setCellPaddings(0.1,0.1,0.1,0.1);
    $table->setBorderForCellRange($border_table,5,4);

    $table->writeToCell(7,3, 'TERMS', $font);
    $table->getCell(7,3)->setCellPaddings(0.1,0.1,0.1,0.1);
    $table->setBorderForCellRange($border_table,7,3);
    $table->writeToCell(7,4, 'ACE JOB NO.', $font);
    $table->getCell(7,4)->setCellPaddings(0.1,0.1,0.1,0.1);
    $table->setBorderForCellRange($border_table,7,4);
    $table->writeToCell(8,3, '30 days', $font);
    $table->getCell(8,3)->setCellPaddings(0.1,0.1,0.1,0.1);
    $table->setBorderForCellRange($border_table,8,3);
    $table->writeToCell(8,4, $job->job_id, $font);
    $table->getCell(8,4)->setCellPaddings(0.1,0.1,0.1,0.1);
    $table->setBorderForCellRange($border_table,8,4);
    
    /*
    //Set top table
    $table = $section->addTable();
    //Set borders
    $table->setBorderForCellRange($border_header,1,2);
    //Add 1 row
    $table->addRow(0.7);
    //Add column
    $table->addColumn(11.8);
    //Set heading quote font
    $quote_font = new PHPRtfLite_Font(20, 'arial', '#000');
    $quote_font->setBold();
    $table->writeToCell(1,1, 'Invoice - ' . _get_invoice_number($job->job_id), $quote_font);
    //Add column
    $table->addColumn(7);
    $cell = $table->getCell(1, 2);
    $image = $cell->addImage($logo);
    $image->setWidth(7);
    $image->setHeight(4);

    //Quote cell
    $cell = $table->getCell(1, 1);
    $cell->setVerticalAlignment('bottom');
    $cell->setBorder($border_header);
    $cell->setCellPaddings(0.5,0,5,1);
    //Image cell
    $cell = $table->getCell(1, 2);
    $cell->setBorder($border_header);
    */
    //Quote info
    /*$qi_table = $section->addTable();

    $qi_table->addRows(3, 0.7);
    $qi_table->addColumnsList(array(3,5,3,2.8,2.5,2.5));    

    $qi_table->setBorderForCellRange($border_full,1,1,3,6);
    for($i = 1; $i <=3; $i++) {
        for($j = 1; $j <= 6; $j++) {
            $cell = $qi_table->getCell($i, $j);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
        }
    }

    $cell = $qi_table->getCell(2, 1);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.2, 0, 0, 0);

    $cell = $qi_table->getCell(2, 2);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.2, 0, 0, 0);

    $qi_table->writeToCell(1, 1, 'Client:', $bold);
    $qi_table->writeToCell(1, 2, $client->field_client_name_value, $small_font);
    $qi_table->writeToCell(1, 3, 'Purchase Order:', $bold);
    $qi_table->writeToCell(1, 4, $job->field_job_po_number_value, $small_font);
    $qi_table->writeToCell(1, 5, 'Ace Job Reference:', $bold);
    $qi_table->writeToCell(1, 6, $job->job_id, $small_font);

    $qi_table->mergeCellRange(2,2,2,6);
    $qi_table->writeToCell(2, 1, 'Address:', $bold);
    $qi_table->writeToCell(2, 2, trim(preg_replace('/\s\s+/', ' ', $client->field_client_company_address_value . ', ' . $client->field_client_company_postcode_value)), $small_font);

    $qi_table->mergeCellRange(3,4,3,6);
    $qi_table->writeToCell(3, 1, 'Booked by:', $bold);
    $qi_table->writeToCell(3, 2, $booked_by, $small_font);
    $qi_table->writeToCell(3, 3, 'Date:', $bold);
    $qi_table->writeToCell(3, 4, date("d/m/Y", $job->created), $small_font);
    */
    /*
    $qi_table2 = $section->addTable();

    $qi_table2->addRows(3,0.7);
    $qi_table2->addColumnsList(array(3,15.8));

    for($i = 1; $i <=3; $i++) {
        for($j = 1; $j <= 2; $j++) {
            $cell = $qi_table2->getCell($i, $j);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
        }
    }

    //Style quote table
    $border = new PHPRtfLite_Border(
        $rtf,                                       // PHPRtfLite instance
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c'), // left border: 2pt, green color
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c'), // top border: 1pt, yellow color
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c'), // right border: 2pt, red color
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c')  // bottom border: 1pt, blue color
    );

    $qi_table2->setBorderForCellRange($border,1,1,3,2);

    $qi_table2->writeToCell(1, 1, 'Venue:', $bold);
    $qi_table2->writeToCell(1, 2, $venue->field_venue_name_value, $small_font);
    $qi_table2->writeToCell(2, 1, 'Address:', $bold);
    $qi_table2->writeToCell(2, 2, trim(preg_replace('/\s\s+/', ' ', $venue->field_venue_address_value)), $small_font);
    $qi_table2->writeToCell(3, 1, 'Postcode:', $bold, $small_font);
    $qi_table2->writeToCell(3, 2, $venue->field_venue_post_code_value, $small_font);
    */
    $job_cancelation_status = '';
    //if ($job->cancellation_status != CANCELLATION_NA) {
    //    $job_cancelation_status = acecrew_get_inv_cancellation_titles($job->cancellation_status);
    //    $job_cancelation_status = '<strong>'. $job_cancelation_status . '</strong>';
    //}
    
    //Listing table top
    $li_top_table = $section->addTable();    
    $li_top_table->addColumnsList(array(1.5,3,1.5,3,1.5,1,1.5,1,0.8,2,2));        
    $li_top_table->addRow(1);
    $li_top_table->mergeCellRange(1,1,1,8);
    //$li_top_table->addColumnsList(array(16,0.8,2,2));
    $li_top_table->writeToCell(1,1, 'Description', $small_font);
    $li_top_table->writeToCell(1,9, '&nbsp;', $small_font);
    $li_top_table->writeToCell(1,10, 'Unit Price', $small_font);
    $li_top_table->writeToCell(1,11, 'Total', $small_font);

    $li_top_table->setBorderForCellRange($border,1,1,1,11);
    $li_top_table->setBorderForCellRange($border,1,1);
    $li_top_table->setBorderForCellRange($border,1,9);
    $li_top_table->setBorderForCellRange($border,1,10);
    $li_top_table->setBorderForCellRange($border,1,11);

    //$li_top_table->addRow(1);
    //$li_top_table->writeToCell(2,1, 'D', $small_font);

    $cell = $li_top_table->getCell(1, 1);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.22, 0, 0, 0);
    $cell = $li_top_table->getCell(1, 10);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.1, 0, 0, 0);
    $cell = $li_top_table->getCell(1,11);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.2, 0, 0, 0);


    $li_top_table->preventEmptyParagraph();
    //Listing table
    //$li_table = $section->addTable();
    //$li_table->addColumnsList(array(1,2,1,2,1,2,1,2,1,2,2));


    $li_table = $section->addTable();
    $li_table->addColumnsList(array(1.5,3,1.5,3,1.5,1,1.5,1,0.8,2,2));  //16,0.8,2,2 //0.8,2,2 // 18.8
    // 1.5,3,1.5,3,1.5,1,1.5,1,0.8,2,2
   
    $li_table->addRow(1);
    $li_table->setBorderForCellRange($border,$row,1,$row,11);
    //$li_table->mergeCellRange($row,1,$row,11);
    

    $vat = NULL;
    $multiple_vat_values = FALSE;
    foreach ($invoice->invoice_items as $item) {
        if (is_null($vat)) {
            $vat = $item['vat'];
        }

        if ($item['vat'] !== $vat) {
            $multiple_vat_values = TRUE;
        }
    }

    $call_index = 1;
    $sum = 0;
    $row = 0;
    //$callings = array();
    //watchdog('jj', '<pre>'.print_r($job, TRUE).'</pre>');
    //watchdog('ccc', '<pre>'.print_r($callings, TRUE).'</pre>');
    foreach ($callings as $data) {
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

        $row++;

        $li_table->addRow(1);

        $call_cancelation_status = '';
        //if ($call->cancellation_status != CANCELLATION_NA) {
        //    $call_cancelation_status = '<br>'.acecrew_get_inv_cancellation_titles($call->cancellation_status);
        //}

        $li_table->mergeCellRange($row,1,$row,11);
        $li_table->writeToCell($row, 1, 'Call: ' . $call_number. '. @ '. $venue_name . $venue_code . $call_cancelation_status, $bold);
        $cell = $li_table->getCell($row, 1);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0); //0.2                

        $row++;
        $li_table->addRow(0.7);

        $call_amount = 0;
        
        // get call data from crew call table
        $call_data = _get_call_data($call);

        // date & time
        $date = substr($call->field_job_session_date_time_value, 0, 10);
        $time = substr($call->field_job_session_date_time_value, 11, -3);

        // number of standard crews
        if (acecrew_is_cancellation_notice($call->cancellation_status) ||
          acecrew_is_cancellation_notice($job->cancellation_status)) {
            $number_of_standard_crews = $call->field_job_session_crew_value;
        } else {
            $number_of_standard_crews = count($call_data);          
        } 

        // quoted hours
        $quoted_hours = $call->field_job_session_hours_value;

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
            while ($r = db_fetch_object($result)) {
                $supp = node_load($r->supplement_id);
                $supplements[$r->supplement_id]['title'] = $supp->title;
                $supplements[$r->supplement_id]['quantity']++;
                if ($r->client_ph != NULL) {
                    $supplements[$r->supplement_id]['amount'] += $r->client_ph * ($call->field_job_session_hours_value + $dat->additional_hours);
                    $call_amount += $r->client_ph * ($call->field_job_session_hours_value + $dat->additional_hours);
                } else {
                    $supplements[$r->supplement_id]['amount'] += $r->client_of;
                    $call_amount += $r->client_of;
                }
                //$call_amount += $supplements[$r->supplement_id]['amount'];
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
        if ($total_adjust_add || $total_adjust_reduce) {
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
        /*
        // half totals for >24hrs&<12hrs
        if ($call->cancellation_status == CANCELLATION_24HOURS_LESS_NOTICE) {
            $sum += ($call_amount / 2);
        } 
        // exclude >24hrs variant - it should be absent for Total Sum
        elseif ($call->cancellation_status != CANCELLATION_24HOURS_MORE_NOTICE) {
            $sum += $call_amount;
        }*/

        if ($additional_hours > 0) $inc++;

        //Date
        $li_table->writeToCell($row,1,'Date:', $small_font);
        $li_table->writeToCell($row,2, $date, $small_font);

        $cell = $li_table->getCell($row, 1);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
        $cell = $li_table->getCell($row, 2);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);

        //Time
        $li_table->writeToCell($row,3,'Time:', $small_font);
        $li_table->writeToCell($row,4, $time, $small_font);

        $cell = $li_table->getCell($row, 3);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
        $cell = $li_table->getCell($row, 4);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);

        //Crew
        $li_table->writeToCell($row,5,'Crew:', $small_font);
        $li_table->writeToCell($row,6, $number_of_standard_crews, $small_font);

        $cell = $li_table->getCell($row, 5);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
        $cell = $li_table->getCell($row, 6);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);

        //Hours
        $li_table->writeToCell($row,7,'Hours:', $small_font);
        $li_table->writeToCell($row,8, $quoted_hours, $small_font);

        $cell = $li_table->getCell($row, 7);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
        $cell = $li_table->getCell($row, 8);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);

        //=
        $li_table->writeToCell($row,9,'=', $small_font);

        $cell = $li_table->getCell($row, 9);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);        
        // Unit price
        $li_table->writeToCell($row,10, ($total_adjusted ? "" : '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($quoted_amount, 'unit_price', $call->cancellation_status, $job->cancellation_status))), $small_font);
        $unit_price_total = $total_adjusted ? ($quoted_amount * $number_of_standard_crews + $total_adjust_add - $total_adjust_reduce) : ($quoted_amount * $number_of_standard_crews);
                
        // Total
        $li_table->writeToCell($row, 11, '&pound;' . ($total_adjusted ? sprintf("%01.2f", acecrew_cancellation_price($unit_price_total, $call->cancellation_status, $job->cancellation_status)) : sprintf("%01.2f", acecrew_cancellation_price($unit_price_total, 'total', $call->cancellation_status, $job->cancellation_status) )), $small_font);

        $cell = $li_table->getCell($row, 10);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
        $cell = $li_table->getCell($row, 11);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);

        if ($additional_hours > 0) {
            $row++;
            $li_table->addRow(0.7);
            $li_table->mergeCellRange($row,1,$row,8);
            $li_table->writeToCell($row, 1, "Includes $additional_hours additional hours", $small_font);
            $li_table->writeToCell($row, 9, "&#xd7;", $small_font);
            $li_table->writeToCell($row, 10, "&pound;" . sprintf("%01.2f", acecrew_cancellation_price($client_rate, 'unit_price', $call->cancellation_status, $job->cancellation_status)), $small_font);
            $li_table->writeToCell($row, 11, "&pound;" . sprintf("%01.2f", acecrew_cancellation_price($client_rate * $additional_hours, 'total', $call->cancellation_status, $job->cancellation_status)), $small_font);

            $cell = $li_table->getCell($row, 1);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 9);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 10);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 11);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
        }

        if ($call->field_add_boundary_charge_value == 1) {
            $row++;
            $li_table->addRow(0.7);
            $li_table->mergeCellRange($row,1,$row,4);
            $li_table->mergeCellRange($row,5,$row,8);
            $li_table->writeToCell($row, 1, 'Boundary Charge:', $small_font);
            $li_table->writeToCell($row, 5, $call->field_job_session_crew_value, $small_font);
            $li_table->writeToCell($row, 9, "&#xd7;", $small_font);
            $def_bound_charge = get_default_boundary_charge();            
            $li_table->writeToCell($row, 10, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($def_bound_charge, 'unit_price', $call->cancellation_status, $job->cancellation_status)), $small_font);
            $li_table->writeToCell($row, 11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($boundary_charge, 'total', $call->cancellation_status, $job->cancellation_status)), $small_font);

            $cell = $li_table->getCell($row, 1);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 5);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 9);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 10);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 11);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);

        }


        if ($call->field_session_num_vehicles_value >= 1) {
            $row++;
            $li_table->addRow(0.7);
            $li_table->mergeCellRange($row,1,$row,4);
            $li_table->mergeCellRange($row,5,$row,8);
            $li_table->writeToCell($row, 1, 'Mileage Charge(' . $distance . ' miles)', $small_font);
            $li_table->writeToCell($row, 5, $call->field_session_num_vehicles_value, $small_font);
            $li_table->writeToCell($row, 9, "&#xd7;", $small_font);
            $li_table->writeToCell($row, 10, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($mileage_unit, 'unit_price', $call->cancellation_status, $job->cancellation_status)), $small_font);
            $li_table->writeToCell($row, 11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($mileage_charge, 'total', $call->cancellation_status, $job->cancellation_status)), $small_font);

            $cell = $li_table->getCell($row, 1);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 5);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 9);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 10);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 11);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
        }


        if ($additional_client_charge >= 1) {
            $row++;
            $li_table->addRow(0.7);
            $li_table->mergeCellRange($row,1,$row,2);
            $li_table->mergeCellRange($row,3,$row,8);
            //$li_table->mergeCellRange($row,9,$row,10);            
            $li_table->writeToCell($row, 1, 'Additional Charges:', $small_font);
            $li_table->writeToCell($row, 3, $additional_client_desc, $small_font);
            $li_table->writeToCell($row, 9, '&#xd7;', $small_font);
            $li_table->writeToCell($row, 10, '', $small_font);
            $li_table->writeToCell($row, 11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($additional_client_charge, 'total', $call->cancellation_status, $job->cancellation_status)), $small_font);

            $cell = $li_table->getCell($row, 1);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 3);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 9);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 11);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
        }

        foreach($supplements as $supplement) {
            if($supplement['amount']) {

                $row++;
                $li_table->addRow(0.7);
                $li_table->mergeCellRange($row,1,$row,4);
                $li_table->mergeCellRange($row,5,$row,8);
                $li_table->writeToCell($row, 1, $supplement['title'], $small_font);
                $li_table->writeToCell($row, 5, $supplement['quantity'], $small_font);
                $li_table->writeToCell($row, 9, '&#xd7;', $small_font);
                $li_table->writeToCell($row, 10, '', $small_font);
                $li_table->writeToCell($row, 11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($supplement['amount'], 'total', $call->cancellation_status, $job->cancellation_status)), $small_font);

                $cell = $li_table->getCell($row, 1);
                $cell->setVerticalAlignment('center');
                $cell->setCellPaddings(0.2, 0, 0, 0);
                $cell = $li_table->getCell($row, 5);
                $cell->setVerticalAlignment('center');
                $cell->setCellPaddings(0.2, 0, 0, 0);
                $cell = $li_table->getCell($row, 9);
                $cell->setVerticalAlignment('center');
                $cell->setCellPaddings(0.2, 0, 0, 0);
                $cell = $li_table->getCell($row, 10);
                $cell->setVerticalAlignment('center');
                $cell->setCellPaddings(0.2, 0, 0, 0);
                $cell = $li_table->getCell($row, 11);
                $cell->setVerticalAlignment('center');
                $cell->setCellPaddings(0.2, 0, 0, 0);
            }
        }

        if ($additional_charge != 0) {

            $row++;
            $li_table->addRow(0.7);
            $li_table->mergeCellRange($row,1,$row,8);
            $li_table->mergeCellRange($row,9,$row,10);
            $li_table->writeToCell($row, 1, 'Additional costs:', $small_font);
            $li_table->writeToCell($row, 9, '=', $small_font);
            $li_table->writeToCell($row, 11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($additional_charge, 'total', $call->cancellation_status, $job->cancellation_status)), $small_font);
            $cell = $li_table->getCell($row, 1);
            $cell->setVerticalAlignment('center');            
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 9);
            $cell->setVerticalAlignment('center');            
            $cell->setCellPaddings(0.2, 0, 0, 0);
            $cell = $li_table->getCell($row, 11);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
        }

        $call_index++;
    }
    
    /*$row++;
    $li_table->addRow(0.7);
    $li_table->mergeCellRange($row,1,$row,11);
    $li_table->writeToCell($row, 1, 'NOTES:', $small_font);

    $cell = $li_table->getCell($row, 1);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.2, 0, 0, 0);
    */

    if ($discount >= 1) {

        $row++;
        $li_table->addRow(0.7);
        $li_table->mergeCellRange($row,1,$row,2);
        $li_table->mergeCellRange($row,3,$row,10);
        $li_table->writeToCell($row, 1, 'Discount:', $small_font);
        $li_table->writeToCell($row, 3, $discount_desc, $small_font);
        $li_table->writeToCell($row, 11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($discount, 'discount', $call->cancellation_status, $job->cancellation_status)), $small_font);

        $cell = $li_table->getCell($row, 1);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
        $cell = $li_table->getCell($row, 3);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
        $cell = $li_table->getCell($row, 11);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
    }

    $sum -= $discount;

    $vat = round(getVAT() * $sum / 100, 2);

    //Total
    $row++;
    $li_table->addRow(0.7);
    $li_table->mergeCellRange($row,1,$row,10);
    $li_table->writeToCell($row, 1, 'Total (Excluding VAT)', $small_font);
    $li_table->writeToCell($row, 11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($sum, 'excluding_vat', $call->cancellation_status, $job->cancellation_status)), $small_font);

    $cell = $li_table->getCell($row, 1);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0, 0, 0.3, 0);
    $cell->setTextAlignment('right');

    $cell = $li_table->getCell($row, 11);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.2, 0, 0, 0);

    //Vat
    $row++;
    $li_table->addRow(0.7);
    $li_table->mergeCellRange($row,1,$row,10);
    $li_table->writeToCell($row, 1, '+ VAT', $small_font);
    $li_table->writeToCell($row, 11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($vat, 'vat', $call->cancellation_status, $job->cancellation_status)), $small_font);

    $cell = $li_table->getCell($row, 1);
    $cell->setVerticalAlignment('center');$cell->setCellPaddings(0, 0, 0.3, 0);
    $cell->setTextAlignment('right');

    $cell = $li_table->getCell($row, 11);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.2, 0, 0, 0);

    //End total
    $row++;
    $li_table->addRow(0.7);
    $li_table->mergeCellRange($row,1,$row,10);
    $li_table->writeToCell($row, 1, 'TOTAL', $small_font);
    $li_table->writeToCell($row, 11, '&pound;' . (sprintf("%01.2f", acecrew_cancellation_price($sum + $vat, 'including_vat', $call->cancellation_status, $job->cancellation_status))), $small_font);

    $cell = $li_table->getCell($row, 1);
    $cell->setVerticalAlignment('center');$cell->setCellPaddings(0, 0, 0.3, 0);
    $cell->setTextAlignment('right');

    $cell = $li_table->getCell($row, 11);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.2, 0, 0, 0);
    
    $credit_image = dirname(__FILE__) . '/../theme/invoice-footer-credit.png';
    $settings = db_fetch_object(db_query("SELECT * FROM {content_type_admin_settings}"));
    $li_table->setBorderForCellRange($border,1,1,$row,11);
    $li_table->preventEmptyParagraph();
    $font = new PHPRtfLite_Font(11, 'arial', '#000');
    //Set bottom table    
    $table = $section->addTable();
    //Add 2 row    
    $table->addColumnsList(array(6.5,6.5));

    $row = 1;
    $notes = trim($job->field_invoice_notes_value);
    if (!empty($notes)) {
        $font_red = new PHPRtfLite_Font(10, 'arial', '#f00');
        $table->addRow(0.7);    
        $table->mergeCellRange($row,1,$row,2); 
        $table->getCell($row,1)->setCellPaddings(0.2,0,0,0);
        $table->getCell($row,1)->setVerticalAlignment('center');
        $table->writeToCell($row,1, $notes, $font_red);
        $row++;
    }

    $table->addRow(1);    
    //$table->mergeCellRange(2,3,2,4);    
    $cell = $table->getCell($row,1);    
    $cell->setCellPaddings(0.7,0,0,0);
    $cell->setVerticalAlignment('center');
    $image = $cell->addImage($credit_image);
    $image->setWidth(5);
    $image->setHeight(2);
    $table->writeToCell($row, 2, 'BACS details:<br/>Account Name: Ace Crew Ltd<br/>Account Number: 30724459<br/>Sort Code: 20-96-55<br/>IBAN:<br/>GB18BARC20965530724459<br/>SWIFT: BARCGB22', 
    $font);
    $table->getCell($row,2)->setCellPaddings(0.3,0.3,0.3,0.3);

    $table->addRow(1);
    $row++;
    $table->writeToCell($row, 1, 'VAT Reg No: 918965374<br/>Company No: 06128298', $font);
    $table->getCell($row,1)->setCellPaddings(0.3,0.3,0.3,0.3);
    $table->writeToCell($row, 2, 'Ace Crew Ltd<br/>Unit 6 Princess Court, Horace<br/>Road,<br/>Kingston Upon Thames, KT1<br/>2SL', 
    $font);
    $table->getCell($row,2)->setCellPaddings(0.3,0.3,0.3,0.3);
    $table->setBorderForCellRange($border,1,1,$row,2);

    // red label
    $section->setSpaceBetweenColumns(0.2);
    $message_font = new PHPRtfLite_Font(11, 'Arial', '#ff0000');
    $message_text_format = new PHPRtfLite_ParFormat();
    $message_text_format->setIndentLeft(0);
    $message_text_format->setIndentRight(0);
    $message_text_format->setTextAlignment('left');
    $section->writeText('FYI - We have launched our new Man & Van service, we have long wheel based lutons available from as little as 2hours. Please enquire.', $message_font, $message_text_format);

    $footer_text = $settings->field_inv_footer_text_value;
    $footer_font = new PHPRtfLite_Font(9, 'Arial', '#555555');

    $footer_text_format = new PHPRtfLite_ParFormat();
    $footer_text_format->setTextAlignment('center');

    /*$cell = $table->getCell(1, 2);
    $image = $cell->addImage($logo);
    $image->setWidth(7);
    $image->setHeight(4);*/

    /*$footer = $section->addFooter();
    $footer->writeText($footer_text, $footer_font, $footer_text_format);
    $image = $footer->addImage($credit_image, $footer_text_format);
    $image->setWidth(5.5);
    $image->setHeight(2);    
    */    
    $invoice_id = $quote['job']->acecrew_job_invoice_id;
    $invoice_number = acecrew_get_invoice_number_by_id($invoice_id);
    $file =  dirname(__FILE__) . '/../rtf/files/Ace-Invoice-'.$invoice_number.'.rtf';

    $rtf->save($file);

    return;
}
