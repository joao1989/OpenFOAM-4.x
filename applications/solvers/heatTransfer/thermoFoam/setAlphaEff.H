Info<< "Creating turbulence model\n" << endl;
tmp<volScalarField> talphaEff;

IOobject turbulencePropertiesHeader
(
    "turbulenceProperties",
    runTime.constant(),
    mesh,
    IOobject::MUST_READ_IF_MODIFIED,
    IOobject::NO_WRITE,
    false
);

if (turbulencePropertiesHeader.headerOk())
{
    autoPtr<compressible::turbulenceModel> turbulence
    (
        compressible::turbulenceModel::New
        (
            rho,
            U,
            phi,
            thermo
        )
    );

    talphaEff = turbulence->alphaEff();
}
else
{
    talphaEff = tmp<volScalarField>
    (
        new volScalarField
        (
            IOobject
            (
                "alphaEff",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar("0", dimMass/dimLength/dimTime, 0.0)
        )
    );
}
