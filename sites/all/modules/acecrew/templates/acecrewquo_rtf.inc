<?php

function _acecrew_quote_get_template_output($quote, $type=NULL) {
    global $base_url;

    $job = $quote['job'];
    $client = $quote['client'];
    $client_contact = $quote['client_contact'];
    $booked_by = $quote['job']->field_job_booked_by_value;
    $job_number = $quote['job']->field_job_number_value;
    $venue = $quote['venue'];
    $callings = $quote['callings'];    

    $logo = dirname(__FILE__) . '/../theme/acecrewquo.png';

    PHPRtfLite::registerAutoloader();

    $rtf = new PHPRtfLite();
    //Set page margins
    $rtf->setMargins(1, 0.2, 1, 0);

    $section = $rtf->addSection();

    //Set top table
    $table = $section->addTable();
    $border = new PHPRtfLite_Border(
        $rtf,                                       // PHPRtfLite instance
        new PHPRtfLite_Border_Format(1, '#fff'), // left border: 2pt, green color
        new PHPRtfLite_Border_Format(1, '#fff'), // top border: 1pt, yellow color
        new PHPRtfLite_Border_Format(1, '#fff'), // right border: 2pt, red color
        new PHPRtfLite_Border_Format(1, '#000')  // bottom border: 1pt, blue color
    );

    $bold = new PHPRtfLite_Font(10);
    $bold->setBold();
    $small_font = new PHPRtfLite_Font(10);

    //Set borders
    $table->setBorderForCellRange($border,1,2);
    //Add 1 row
    $table->addRow(0.7);
    //Add column
    $table->addColumn(11.8);
    //Set heading quote font
    $quote_font = new PHPRtfLite_Font(20, 'arial', '#000');
    $quote_font->setBold();
    $table->writeToCell(1,1, 'Quote - '.$job_number, $quote_font);
    //$table->writeToCell(1,1, 'Quote', $quote_font);
    //Add column
    $table->addColumn(7);
    $cell = $table->getCell(1, 2);
    $image = $cell->addImage($logo);
    $image->setWidth(7);
    $image->setHeight(4);

    //Quote cell
    $cell = $table->getCell(1, 1);
    $cell->setVerticalAlignment('bottom');
    $cell->setBorder($border);
    $cell->setCellPaddings(0.5,0,5,1);
    //Image cell
    $cell = $table->getCell(1, 2);
    $cell->setBorder($border);

    //Quote info
    $qi_table = $section->addTable();

    $qi_table->addRows(2, 0.7);
    $qi_table->addColumnsList(array(3,6,3,6.8));

    //Style quote table
    $border = new PHPRtfLite_Border(
        $rtf,                                       // PHPRtfLite instance
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c'), // left border: 2pt, green color
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c'), // top border: 1pt, yellow color
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c'), // right border: 2pt, red color
        new PHPRtfLite_Border_Format(0.1, '#8c8c8c')  // bottom border: 1pt, blue color
    );

    $qi_table->setBorderForCellRange($border,1,1,2,4);
    for($i = 1; $i <=2; $i++) {
        for($j = 1; $j <= 4; $j++) {
            $cell = $qi_table->getCell($i, $j);
            $cell->setVerticalAlignment('center');
            $cell->setCellPaddings(0.2, 0, 0, 0);
        }
    }

    $qi_table->writeToCell(1, 1, 'Client:', $bold);
    $qi_table->writeToCell(1, 2, $client->field_client_name_value, $small_font);
    $qi_table->writeToCell(1, 3, 'Reference:', $bold);
    $qi_table->writeToCell(1, 4, $job->job_id, $small_font);
    $qi_table->writeToCell(2, 1, 'Booked by:', $bold);
    $qi_table->writeToCell(2, 2, $booked_by, $small_font);
    $qi_table->writeToCell(2, 3, 'Date:', $bold);
    $qi_table->writeToCell(2, 4, date("d/m/Y", $job->created), $small_font);


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

    //Listing table top
    $li_top_table = $section->addTable();
    $li_top_table->addRow(0.7);
    $li_top_table->addColumnsList(array(14,0.8,2,2));
    $li_top_table->writeToCell(1,1, '', $small_font);
    $li_top_table->writeToCell(1,2, '', $small_font);
    $li_top_table->writeToCell(1,3, 'Unit Price', $small_font);
    $li_top_table->writeToCell(1,4, 'Total', $small_font);

    $li_top_table->setBorderForCellRange($border,1,1,1,4);

    $cell = $li_top_table->getCell(1, 3);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.1, 0, 0, 0);
    $cell = $li_top_table->getCell(1,4);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.2, 0, 0, 0);


    $li_top_table->preventEmptyParagraph();
    //Listing table
    //$li_table = $section->addTable();
    //$li_table->addColumnsList(array(1,2,1,2,1,2,1,2,1,2,2));


    $li_table = $section->addTable();
    $li_table->addColumnsList(array(1.5,3,1.5,3,1.5,1,1.5,1,0.8,2,2));


    $call_index = 1;
    $sum = 0;
    $row = 0;
    foreach ($callings as $data) {
        $row++;

        $call = $data['data'];
        
        $call_number = explode('-', $call->field_session_callid_value);
        $call_number = $call_number[1];

        if ($call->field_job_session_plus_call_value === '1') {
          $call->field_job_session_hours_value = $call->field_job_session_hours_value.'+';
        } 

        $venue = acecrew_get_venue_by_id($call->field_job_session_venue_value);
        $venue_name = $venue->field_venue_name[0]['value'];

        $li_table->addRow(1);

        $li_table->mergeCellRange($row,1,$row,11);;
        $li_table->writeToCell($row, 1, 'Call: ' . $call_number . '. @ ' . $venue_name, $bold);
        $cell = $li_table->getCell($row, 1);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);

        $row++;
        $li_table->addRow(0.7);


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

        //Date
        $li_table->writeToCell($row,1,'Date:', $small_font);
        $li_table->writeToCell($row,2, substr($call->field_job_session_date_time_value, 0, 10), $small_font);

        $cell = $li_table->getCell($row, 1);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
        $cell = $li_table->getCell($row, 2);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);

        //Time
        $li_table->writeToCell($row,3,'Time:', $small_font);
        $li_table->writeToCell($row,4, substr($call->field_job_session_date_time_value, 11, 20), $small_font);

        $cell = $li_table->getCell($row, 3);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
        $cell = $li_table->getCell($row, 4);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);

        //Crew
        $li_table->writeToCell($row,5,'Crew:', $small_font);
        $li_table->writeToCell($row,6, $call->field_job_session_crew_value, $small_font);

        $cell = $li_table->getCell($row, 5);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
        $cell = $li_table->getCell($row, 6);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);

        //Hours
        $li_table->writeToCell($row,7,'Hours:', $small_font);
        $li_table->writeToCell($row,8, $call->field_job_session_hours_value, $small_font);

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

        //Unit price
        $li_table->writeToCell($row,10, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($call_amount, 'unit_price', $call->cancellation_status, $job->cancellation_status)), $small_font);
        //Unit price
        $li_table->writeToCell($row,11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($total, 'total', $call->cancellation_status, $job->cancellation_status)), $small_font);

        $cell = $li_table->getCell($row, 10);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);
        $cell = $li_table->getCell($row, 11);
        $cell->setVerticalAlignment('center');
        $cell->setCellPaddings(0.2, 0, 0, 0);


        if ($call->field_add_boundary_charge_value == 1) {
            $default_boundary_charge = get_default_boundary_charge();
            $row++;
            $li_table->addRow(0.7);
            $li_table->mergeCellRange($row,1,$row,4);
            $li_table->mergeCellRange($row,5,$row,8);
            $li_table->writeToCell($row, 1, 'Boundary Charge:', $small_font);
            $li_table->writeToCell($row, 5, $call->field_job_session_crew_value, $small_font);
            $li_table->writeToCell($row, 9, "&#xd7;", $small_font);
            $li_table->writeToCell($row, 10, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($default_boundary_charge, 'unit_price', $call->cancellation_status, $job->cancellation_status)), $small_font);
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
            $li_table->writeToCell($row, 10, '&pound;' .sprintf("%01.2f", acecrew_cancellation_price($mileage_unit, 'unit_price', $call->cancellation_status, $job->cancellation_status)), $small_font);
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
            $li_table->mergeCellRange($row,1,$row,4);
            $li_table->mergeCellRange($row,5,$row,8);
            $li_table->writeToCell($row, 1, 'Additional Charges:', $small_font);
            $li_table->writeToCell($row, 5, $additional_client_desc, $small_font);
            $li_table->writeToCell($row, 9, '', $small_font);
            $li_table->writeToCell($row, 10, '=', $small_font);
            $li_table->writeToCell($row, 11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($additional_client_charge, 'total', $call->cancellation_status, $job->cancellation_status)), $small_font);

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

        $li_table->mergeCellRange(1,12,2,12);

        $total += $additional_client_charge;
        $total += $boundary_charge;
        $total += $mileage_charge;        
        $supplement_total = 0;
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
                $row++;
                $li_table->addRow(0.7);
                $li_table->mergeCellRange($row,1,$row,4);
                $li_table->mergeCellRange($row,5,$row,8);
                $li_table->writeToCell($row, 1, $node->title, $small_font);
                $li_table->writeToCell($row, 5, $quantity, $small_font);
                $li_table->writeToCell($row, 9, '', $small_font);
                $li_table->writeToCell($row, 10, '', $small_font);
                $li_table->writeToCell($row, 11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($value, 'total', $call->cancellation_status, $job->cancellation_status)), $small_font);

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
            $supplement_total += $value;
        }
        $call_index++;
        $total = $total + $supplement_total;
        $sum += acecrew_cancellation_price_total($total, 
                                                 $call->cancellation_status, 
                                                 $job->cancellation_status);
    }

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
    $li_table->writeToCell($row, 11, '&pound;' . sprintf("%01.2f", acecrew_cancellation_price($sum + $vat, 'including_vat', $call->cancellation_status, $job->cancellation_status)), $small_font);

    $cell = $li_table->getCell($row, 1);
    $cell->setVerticalAlignment('center');$cell->setCellPaddings(0, 0, 0.3, 0);
    $cell->setTextAlignment('right');

    $cell = $li_table->getCell($row, 11);
    $cell->setVerticalAlignment('center');
    $cell->setCellPaddings(0.2, 0, 0, 0);


    $settings = db_fetch_object(db_query("SELECT * FROM {content_type_admin_settings}"));
    $footer_text = $settings->field_quo_footer_text_value;
    $footer_font = new PHPRtfLite_Font(9, 'Arial', '#555555');

    $footer_text_format = new PHPRtfLite_ParFormat();
    $footer_text_format->setTextAlignment('center');


    $footer = $section->addFooter();
    $footer->writeText($footer_text, $footer_font, $footer_text_format);


    /* End rtf */
    $li_table->setBorderForCellRange($border,1,1,$row,11);
    $quote_id = $quote['job']->acecrew_job_quote_id;
    $job_number = acecrew_get_job_by_quote_id($quote_id);
    $file =  dirname(__FILE__) . '/../rtf/files/Ace-Quote-'.$job_number.'.rtf';

    $rtf->save($file);

    return;
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
