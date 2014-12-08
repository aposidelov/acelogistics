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
function _invoice_acecrewquo_get_template_output($invoice, $type=NULL) {
  ob_start();
  
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
   
  $footer_content_s1 = 'T +44 (0)207 924 6569   F +44 (0)207 900 6569   M +44(0)7947 88 66 99';
  $footer_content_s2 = '126 Bolingbroke grove, Clapham Junction, SW11 1DA.';
  $footer_content_s3 = 'admin@acecrew.co.uk     www.acecrew.co.uk';
  $footer_content_s4 = 'Company No: 6128298';
  
  if ($type == 'pdf') {
    $footer = '<script type="text/php">
                if (isset($pdf)) {
                  // Open the object: all drawing commands will
                  // go to the object instead of the current page
                  $footer = $pdf->open_object();

                  // Get page width and height
                  $w = $pdf->get_width();
                  $h = $pdf->get_height();
                  
                  // Get font
                  $font = Font_Metrics::get_font("arial");
                  
                  // Set RGB line color
                  $r=128; $g=128; $b=128;
                  
                  // Leave this array alone                  
                  $a_line_color = array(0 => $r / 0xff, 1 => $g / 0xff, 2 => $b / 0xff,
                    "r"=>$r / 0xff, "g"=>$g / 0xff, "b"=>$b / 0xff,
                    "hex" => sprintf("#%02X%02X%02X", $r, $g, $b));
                  
                  // Leave this array alone                  
                  $a_text_color = array(0 => $r / 0xff, 1 => $g / 0xff, 2 => $b / 0xff,
                    "r"=>$r / 0xff, "g"=>$g / 0xff, "b"=>$b / 0xff,
                    "hex" => sprintf("#%02X%02X%02X", $r, $g, $b));
                    
                  // Set line
                  $pdf->line(40, $h-60, $w-40, $h-60, $a_line_color, 1, array()); 
                    
                  // Set page text
                  $footer_content_font_size = 8;
                  $footer_content_font_space = 1;
                  
                  $footer_content_s1 = \'' . $footer_content_s1 . '\';
                  $footer_content_s2 = \'' . $footer_content_s2 . '\';
                  $footer_content_s3 = \'' . $footer_content_s3 . '\';
                  $footer_content_s4 = \'' . $footer_content_s4 . '\';
                  
                  
                  $footer_content_s1_len  = $pdf->get_text_width($footer_content_s1, $font, $footer_content_font_size);
                  $footer_content_s2_len  = $pdf->get_text_width($footer_content_s2, $font, $footer_content_font_size);
                  $footer_content_s3_len  = $pdf->get_text_width($footer_content_s3, $font, $footer_content_font_size);
                  $footer_content_s4_len  = $pdf->get_text_width($footer_content_s4, $font, $footer_content_font_size);
                  
                  $pdf->text(($w - $footer_content_s1_len) / 2, $h - 60 + $footer_content_font_space, $footer_content_s1, $font, $footer_content_font_size, $a_text_color);
                  $pdf->text(($w - $footer_content_s2_len) / 2, $h - 60 + $footer_content_font_space*2 + $footer_content_font_size, $footer_content_s2, $font, $footer_content_font_size, $a_text_color);
                  $pdf->text(($w - $footer_content_s3_len) / 2, $h - 60 + $footer_content_font_space*3 + $footer_content_font_size*2, $footer_content_s3, $font, $footer_content_font_size, $a_text_color);
                  $pdf->text(($w - $footer_content_s4_len) / 2, $h - 60 + $footer_content_font_space*4 + $footer_content_font_size*3, $footer_content_s4, $font, $footer_content_font_size, $a_text_color);
                  
                  $pdf->page_text($w-57, $h-39, "{PAGE_NUM}/{PAGE_COUNT}", $font, 10, $a_text_color);
                  
                  // Close the object (stop capture)
                  $pdf->close_object();
                
                  // Add the object to every page. You can
                  // also specify "odd" or "even"
                  $pdf->add_object($footer, "all");
                }
                </script>';
    echo $footer;
    $footer = '';
  }
  else {
    $footer = $footer_content;    
  }
     
   $image = url(drupal_get_path('module', 'acecrew') . '/theme/acecrewquo.png', array('absolute' => true));
   
  echo '
  <table class="acecrew_top_tbl">
  <tr>
    <td class="acecrew_logo">
        <img src="' . $image . '" alt="Acecrew" title="Acecrew" />
             
    </td>
  </tr>
  <tr>
    <td class="top_strings">
    
    </td>
  </tr>  
  </table>
  
  <hr class="acecrew_head_separator" />
  <h1>' . t('Quote') . '</h1>
  <table class="acecrew_head_tbl">
    <tr>
        <td class="label">' . t('Client') . ':</td> 
        <td>' . $invoice->customer['company_name'] . '</td>
        <td class="label"> ' . t('Reference') . ':</td>
        <td> ' . $invoice->invoice['formatted_invoice_number'] . ' </td>
    </tr>
    <tr> 
        <td class="label">' . t('Contact') . ':</td>
        <td>' . $invoice->customer['firstname'] . '</td>
        <td class="label">'. t('Date') .':</td>
        <td>'. $invoice->invoice['formatted_created'] .'</td>
    </tr>
  </table>
  
  <p class="venue">
    ' . t('Venue') . ': ' . $invoice->customer['street'] . '
  </p>';
  
  // If an invoice has items with different vat values this column must always be shown.
  $vat = NULL;
  $multiple_vat_values = FALSE;  
  foreach ($invoice->invoice_items as $item) {
      
    // Set vat value for the first time
    if (is_null($vat)) {
      $vat = $item['vat'];  
    }
    
    if ($item['vat'] !== $vat) {
      $multiple_vat_values = TRUE;
    }
  }
  
  echo '<ul type="disc" class="total_list"> ';
  
  /*------------ invoice items -------------*/
  foreach ($invoice->invoice_items as $item) {

      //fix encoding problem when convert GBP character to HTML entites
      foreach($item as $key => $value){
        $item[$key] = str_replace('&Acirc;', '', htmlentities($value));
      }

      echo '<li>' . $item["description"] . ' = ' . $item['formatted_extotal'] . '</li>';
  }
  /*--------------- end --------------------*/
  
  echo '</ul>';
  echo '<p class="total_quote"> Total = ' . $invoice->invoice['formatted_extotal'] . ' (excl. VAT) </p>';
  echo '<p class="quote_confirm"> Please confirm all jobs by means of a Purchase Order. </p>';
  
  $content = ob_get_contents(); ob_end_clean();
  return $content;
}
