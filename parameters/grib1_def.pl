#!/usr/local/bin/perl56 -I/usr/local/lib/metaps/perl
use Data::Dumper;
use metdb qw(prod);

use metdb::grib_parameters;

my @x = metdb::grib_parameters->all_fields;
#print Dumper(\@x);
my $last;

open(out,"> grib1_short_name.def");

print out <<"EOF";
# Automatically generated by $0, do not edit

EOF

foreach my $p ( metdb::grib_parameters->find(
	{ },
	[qw(grib_originating_centre grib_code_table grib_parameter)]))
{
	my ($centre,$table)     = ($p->get_grib_originating_centre,$p->get_grib_code_table);
	my ($param,$abbr,$name) = ($p->get_grib_parameter, $p->get_mars_abbreviation,$p->get_long_name);
	$abbr =~ tr/A-Z/a-z/;

    print out "   \'$abbr\' = { indicatorOfParameter=$param ;  gribTablesVersionNo=$table ;}\n" unless(!$abbr);
}

close out;
open(out,"> grib1_name.def");

print out <<"EOF";
# Automatically generated by $0, do not edit

EOF

foreach my $p ( metdb::grib_parameters->find(
	{ },
	[qw(grib_originating_centre grib_code_table grib_parameter)]))
{
	my ($centre,$table)     = ($p->get_grib_originating_centre,$p->get_grib_code_table);
	my ($param,$abbr,$name) = ($p->get_grib_parameter, $p->get_mars_abbreviation,$p->get_long_name);
	$abbr =~ tr/A-Z/a-z/;

    $name =~ s/ /_/g;
    $name =~ s/,//g;
    print out "   \'$name\' = { indicatorOfParameter=$param ;  gribTablesVersionNo=$table ; }\n" unless(!$abbr);
}

close out;
open(out,"> grib1_units.def");

print out <<"EOF";
# Automatically generated by $0, do not edit

EOF

foreach my $p ( metdb::grib_parameters->find(
	{ },
	[qw(grib_originating_centre grib_code_table grib_parameter)]))
{
	my ($centre,$table)     = ($p->get_grib_originating_centre,$p->get_grib_code_table);
	my ($param,$abbr,$unit) = ($p->get_grib_parameter, $p->get_mars_abbreviation,$p->get_unit);
	$abbr =~ tr/A-Z/a-z/;

    print out "   \'$unit\' = { indicatorOfParameter=$param ;  gribTablesVersionNo=$table ; }\n" unless(!$abbr);
}

close out;


__END__
'grib_originating_centre',
'grib_code_table',
'grib_parameter',
'mars_abbreviation',
'long_name',
'description',
'web_title',
'unit',
'comment',
'parameter_type',
'wind_corresponding_parameter',
'netcdf_name',
'netcdf_cf_approved',
'magics_abbreviated_text',
'magics_title',
'magics_offset',
'magics_factor',
'magics_scaled_unit',
'magics_contour_interval',
'magics_specification_group',
'magics_comment',
'dissemination_accuracy',
'dissemination',
'insert_date',
'update_date'

my %x;

foreach my $n ( sort keys %{$info} )
{
	my $p = $info->{$n}->{'mars.param'};
	my $z = $info->{$n};

	if(exists $x{$p})
	{
		# Find differences
		my %z;
		my @z = keys %{$x{$p}};

		foreach my $k ( keys %{$z} )
		{
			$z{$k} = $z->{$k} if($x{$p}->{$k} eq $z->{$k});
		}

		$z = \%z;
	}

	$x{$p} = $z;

}

foreach my $k ( sort { $x{$a}->{tigge_name} cmp $x{$b}->{tigge_name} } keys %x )
{
	print "# $x{$k}->{tigge_name} \n";
	print "   '$k' = {\n";

	foreach my $m ( sort keys %{$x{$k}} )
	{

		next if($m =~ /\./);
		next if($m =~ /\_/);
		my $v = $x{$k}->{$m};
		next if($v =~ /#/);
		next if($v =~ /missing/i);

		print "         $m = $v;\n";
	}

	print "   }\n\n";
}


foreach my $k ( sort { $x{$a}->{'mars.abbreviation'} cmp $x{$b}->{tigge_name} } keys %x )
{
	#print "# $x{$k}->{tigge_name} \n";
	print "   '$x{$k}->{'mars.abbreviation'}' = { parameter = $k; }\n";
}

print <<"EOF";
}

alias ls.short_name=tigge_short_name;

concept tigge_name {
EOF

foreach my $k ( sort { $x{$a}->{tigge_name} cmp $x{$b}->{tigge_name} } keys %x )
{
	print "   '$x{$k}->{tigge_name}' = { parameter = $k; }\n";
}

print <<"EOF";
}
EOF
