function onStepIn(creature, item, position, fromPosition)
	if Game.isItemThere({x = 32243, y = 31892, z = 14}, 2886) and item:getFluidType() == FLUID_BLOOD then
		Game.sendMagicEffect({x = 32242, y = 31891, z = 14}, 1)
		Game.sendMagicEffect({x = 32243, y = 31891, z = 14}, 1)
		Game.sendMagicEffect({x = 32242, y = 31892, z = 14}, 1)
		Game.sendMagicEffect({x = 32242, y = 31893, z = 14}, 1)
		Game.sendMagicEffect({x = 32243, y = 31893, z = 14}, 1)
	else
		doRelocate({x = 32243, y = 31892, z = 14},{x = 32244, y = 31892, z = 14})
		Game.sendMagicEffect({x = 32243, y = 31892, z = 14}, 3)
	end
end

function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 32243, y = 31892, z = 14}, 2886) and item:getFluidType() == FLUID_BLOOD then
		Game.sendMagicEffect({x = 32242, y = 31891, z = 14}, 1)
		Game.sendMagicEffect({x = 32243, y = 31891, z = 14}, 1)
		Game.sendMagicEffect({x = 32242, y = 31892, z = 14}, 1)
		Game.sendMagicEffect({x = 32242, y = 31893, z = 14}, 1)
		Game.sendMagicEffect({x = 32243, y = 31893, z = 14}, 1)
	else
		doRelocate({x = 32243, y = 31892, z = 14},{x = 32244, y = 31892, z = 14})
		Game.sendMagicEffect({x = 32243, y = 31892, z = 14}, 3)
	end
end
