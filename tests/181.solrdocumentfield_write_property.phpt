--TEST--
SolrDocumentField - exception - on write property
--FILE--
<?php

require_once "bootstrap.inc";
$field = new SolrDocumentField();

try {
	$field->myIllegalProperty = 1;
} catch (SolrIllegalOperationException $e) {
	printf("Exception %d: %s", $e->getCode(), $e->getMessage());
}

?>
--EXPECT--
Exception 1007: SolrDocumentField instances are read-only. Properties cannot be updated or removed.
