function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 33233, y = 32692, z = 13},3042) then 
		doRelocate({x = 33234, y = 32692, z = 13},{x = 33234, y = 32687, z = 13})
		Game.sendMagicEffect({x = 33234, y = 32692, z = 13}, 11)
		Game.sendMagicEffect({x = 33234, y = 32687, z = 13}, 11)
		Game.sendMagicEffect({x = 33233, y = 32692, z = 13}, 16)
		Game.removeItemOnMap({x = 33233, y = 32692, z = 13}, 3042)
	else
		Game.sendMagicEffect({x = 33233, y = 32692, z = 13}, 3)
	end
end
