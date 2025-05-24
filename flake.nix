{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
    {
      devShells.aarch64-darwin.default =
        let
          pkgs = import nixpkgs { system = "aarch64-darwin"; };
        in
        pkgs.mkShell {
          buildInputs = with pkgs; [
            zsh
            nixfmt-rfc-style
            nil
            llvm_20
            cmake
          ];
          shellHook = ''
            echo "Welcome to your sugarspice shop dev environment!"
          '';
        };
    };

}
