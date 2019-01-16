function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 33240, y = 32855, z = 13},3042) then 
		doRelocate({x = 33240, y = 32856, z = 13},{x = 33246, y = 32850, z = 13})
		Game.sendMagicEffect({x = 33240, y = 32856, z = 13}, 11)
		Game.sendMagicEffect({x = 33246, y = 32850, z = 13}, 11)
		Game.sendMagicEffect({x = 33240, y = 32855, z = 13}, 16)
		Game.removeItemOnMap({x = 33240, y = 32855, z = 13}, 3042)
	else
		Game.sendMagicEffect({x = 33240, y = 32855, z = 13}, 3)
	end
end
