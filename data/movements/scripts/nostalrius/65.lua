function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 33276, y = 32552, z = 14},3042) then 
		doRelocate({x = 33276, y = 32553, z = 14},{x = 33271, y = 32553, z = 14})
		Game.sendMagicEffect({x = 33276, y = 32553, z = 14}, 11)
		Game.sendMagicEffect({x = 33271, y = 32553, z = 14}, 11)
		Game.sendMagicEffect({x = 33276, y = 32552, z = 14}, 16)
		Game.removeItemOnMap({x = 33276, y = 32552, z = 14}, 3042)
	else
		Game.sendMagicEffect({x = 33276, y = 32552, z = 14}, 3)
	end
end
