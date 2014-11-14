/* matching rule passthru */
/* $OpenLDAP$ */
/* This work is part of OpenLDAP Software <http://www.openldap.org/>.
 *
 * Copyright 2014 The OpenLDAP Foundation.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted only as authorized by the OpenLDAP
 * Public License.
 *
 * A copy of this license is available in the file LICENSE in the
 * top-level directory of the distribution or, alternatively, at
 * <http://www.OpenLDAP.org/license.html>.
 */
/* ACKNOWLEDGEMENTS:
 * This work was initially developed by Pierangelo Masarati for inclusion
 * in OpenLDAP Software.
 */

#include "portable.h"

#include "slap.h"
#include "config.h"
#include "lutil.h"
#include "ac/string.h"

static int
failMatch(
	int *matchp,
	slap_mask_t flags,
	Syntax *syntax,
	MatchingRule *mr,
	struct berval *value,
	void *assertedValue )
{
	int match;
	struct berval *asserted = (struct berval *) assertedValue;

	assert( matchp != NULL );
	assert( value != NULL );
	assert( assertedValue != NULL );
	assert( !BER_BVISNULL( value ) );
	assert( !BER_BVISNULL( asserted ) );

	match = 1;

	*matchp = match;
	return LDAP_SUCCESS;
}

static int
mr_passthru_initialize( void )
{
	static slap_mrule_defs_rec mr_def = {
		"( 1.2.840.113556.1.4.1941 "
			"NAME 'inChain' "
			"SYNTAX 1.3.6.1.4.1.1466.115.121.1.12 "
			"X-PASSTHRU '' "
			")",
			SLAP_MR_HIDE | SLAP_MR_EXT, NULL,
			NULL, dnNormalize, failMatch,
			NULL, NULL,
			NULL
	};

	int			rc;

	/* equality rule */
	rc = register_matching_rule( &mr_def );
	if ( rc != 0 ) {
		return rc;
	}

	return rc;
}

int
init_module( int argc, char *argv[] )
{
	return mr_passthru_initialize();
}
